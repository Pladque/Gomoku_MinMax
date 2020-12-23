import pyautogui
from PIL import Image
import image_slicer
import glob
import time
import numpy
import pyscreenshot as ImageGrab
from board_coords import *
import subprocess
import os
from subprocess import Popen, PIPE
from termcolor import colored

BLACK = (40, 40, 40)
WHITE = (243, 243, 243)
AI = BLACK
OPPONENT = WHITE

# TODO
# rading from file previously calculated doesnt work sometimes idk why
# open file once and save it to list, do not ope it every time
# make loop except of making ss by maniually
# make use of x and y substractors
# make auto clicker


def get_curr_board(ss_gap:int) ->str:
    time.sleep(ss_gap)
    SS = ImageGrab.grab(bbox=(410,130,963,685))
    SS.save("D:\Projects\PythonProjects\PrivateGithub\Tic-Tac-Toe_MinMax\ss.png")

    #create board

    SS = ImageGrab.grab(bbox=(410,130,963,685)).load()
    board_str = ""
    for y in FIELD_Y:
        for x in FIELDS_X:
            if SS[x,y] == OPPONENT:
                board_str += 'O'
            elif SS[x,y] == AI:
                board_str += 'X'
            else:
                board_str+='0'

    return board_str

#search board in file_moves_data_r
def find_in_previously_calculated(board_str:str) -> int:
    file_moves_data_r = open("calculated_moves.txt", 'r')
    move = 0
    for line in file_moves_data_r.readlines():
        if  board_str == line[:line.index(';')].replace(' ', ''):
            move = int(line[line.index(';')+1:].replace(' ', '').replace('\n', ''))
            return move
    file_moves_data_r.close()

    return -1

def save_parameters_to_file(board_str:str, depth:int, left_x_substr:int, right_x_substr:int,left_y_substr:int, right_y_substr:int):
    file_board_w = open("board.txt", 'w')
    file_board_w.write(board_str)
    file_board_w.write('\n')
    file_board_w.write(str(depth))

    file_board_w.write('\n')

    file_board_w.write(str(left_x_substr))
    file_board_w.write('\n')
    file_board_w.write(str(right_x_substr))
    file_board_w.write('\n')
    file_board_w.write(str(left_y_substr))
    file_board_w.write('\n')
    file_board_w.write(str(right_y_substr))

    file_board_w.close()

def run_cpp():
    subprocess.check_call(['D:\Projects\PythonProjects\PrivateGithub\Tic-Tac-Toe_MinMax\MULTITHREAD tictactoe cpp 15x15.exe'])
#o = subprocess.Popen(['cmd','/c',r'D:\Projects\PythonProjects\PrivateGithub\Tic-Tac-Toe_MinMax\EXE\MULTITHREAD tictactoe cpp 15x15.exe'])
#o.wait()  

def print_board_from_file(board_str:str):
    file_move_from_cpp_r = open("string_index_return.txt", 'r')
    ind = file_move_from_cpp_r.readline()
    ind = int(ind)
    ind_x = int(ind) %15
    ind_y = int(int(ind) /15)
    print(ind_x, ind_y)
    file_move_from_cpp_r.close()
    board_list = list(board_str)
    board_list[ind_y * 15 + ind_x] = 'X'        

    for y in range(15):
        for x in range(15):
            if y*15 + x == ind_y * 15 + ind_x:
                print(colored(board_list[y*15 + x], 'blue', 'on_white'), end = '')
            elif board_list[y*15 + x] == 'O':
                print(colored(board_list[y*15 + x], 'red'), end = '')
            elif board_list[y*15 + x] == 'X':
                print(colored(board_list[y*15 + x], 'green'), end = '')
            elif board_list[y*15 + x] == '0':
                print(colored(board_list[y*15 + x], 'white'), end = '')
                
                
        print()
#read file_move_from_cpp_r file
#convert it to coords
#click on right spot on screen

if __name__ == '__main__':
    board_str = get_curr_board(1)
    move = find_in_previously_calculated(board_str)
    if move != -1:
        board_str[move] = AI
    else:
        save_parameters_to_file(board_str, 5, 0, 14, 0, 14)
        run_cpp()
    print_board_from_file(board_str)


