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
from pynput.mouse import Button, Controller

BLACK = (40, 40, 40)
WHITE = (243, 243, 243)
AI = WHITE
OPPONENT = BLACK

mouse = Controller()


# TODO
# rading from file previously calculated doesnt work sometimes idk why
# open file once and save it to list, do not ope it every time
# make loop except of making ss by maniually
# make use of x and y substractors
# make auto clicker

MOVES_BASE = {}
LAST_4_MOVES = []


f = open("mouseClickPos.txt", 'r')

lines = f.readlines()
CLICK_X_POSITIONS = [int(coord) for coord in lines[0].replace('\n', '').split(" ")]
CLICK_Y_POSITIONS = [int(coord) for coord in lines[1].split(" ")]

f.close()

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
    if SS[175,284] == (238, 34, 17):
        return "-1"
    return board_str

def create_moves_base():
    file_moves_data_r = open("calculated_moves.txt", 'r')
    for line in file_moves_data_r.readlines():
        MOVES_BASE[line[:line.index(';')].replace(' ', '')] = int(line[line.index(';')+1:].replace(' ', '').replace('\n', ''))
    file_moves_data_r.close()


#search board in file_moves_data_r
def find_in_previously_calculated(board_str:str) -> int:
    file_moves_data_r = open("calculated_moves.txt", 'r')
    move = 0
    for line in file_moves_data_r.readlines():
        if  board_str == line[:line.index(';')].replace(' ', ''):
            move = int(line[line.index(';')+1:].replace(' ', '').replace('\n', ''))
            return int(move)
    file_moves_data_r.close()

    return -1

def save_parameters_to_file(board_list:list, depth:int, left_x_substr:int, right_x_substr:int,left_y_substr:int, right_y_substr:int):
    file_board_w = open("board.txt", 'w')
    board_str = ''.join(board_list)
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

def get_indexand_print_board_from_file(board_list:list):
    file_move_from_cpp_r = open("string_index_return.txt", 'r')
    ind = file_move_from_cpp_r.readline()
    ind = int(ind)
    ind_x = int(ind) %15
    ind_y = int(int(ind) /15)
    print(ind_x, ind_y)
    file_move_from_cpp_r.close()
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
    print()
    return ind_y * 15 + ind_x

def print_curr_board(board_list:list, move:int):
    ind_x = move % 15
    ind_y = move / 15
    
    for y in range(15):
        for x in range(15):
            if y*15 + x == move:
                print(colored(board_list[y*15 + x], 'blue', 'on_white'), end = '')
            elif board_list[y*15 + x] == 'O':
                print(colored(board_list[y*15 + x], 'red'), end = '')
            elif board_list[y*15 + x] == 'X':
                print(colored(board_list[y*15 + x], 'green'), end = '')
            elif board_list[y*15 + x] == '0':
                print(colored(board_list[y*15 + x], 'white'), end = '')
        print()

def calc_x_y_substractors():
    #LAST_4_MOVES
    return 0, 14,0,14

def click_mouse(move:int):
    ind_x= move % 15
    ind_y = int(move / 15)
    print(ind_x)
    print(ind_y)
    mouse.position = (CLICK_X_POSITIONS[ind_x],CLICK_Y_POSITIONS[ind_y])
    mouse.click(Button.left, 1)

def read_postions_to_click():
    f = open("mouseClickPos.txt", 'r')

    lines = f.readlines()
    CLICK_X_POSITIONS = [int(coord) for coord in lines[0].replace('\n', '').split(" ")]
    CLICK_Y_POSITIONS = [int(coord) for coord in lines[1].split(" ")]

    f.close()


#read file_move_from_cpp_r file
#convert it to coords
#click on right spot on screen

if __name__ == '__main__':
    create_moves_base()
    read_postions_to_click()
    board_list = []
    x_l_substr, x_r_range, y_l_substr, y_r_range =  0, 14, 0, 14
    depth = 5
    while True:
        temp_board_str = get_curr_board(1)
        if temp_board_str == "-1":
            break
        #print(list(temp_board_str))
        #print(board_list)
        while ''.join(board_list) == temp_board_str:
            temp_board_str = get_curr_board(1)
        board_list = list(temp_board_str)
        #move = find_in_previously_calculated(board_str)
        move = 0
        if ''.join(board_list) in MOVES_BASE.keys():
            move = MOVES_BASE[''.join(board_list)]
            board_list[move] = 'X'
            print_curr_board(board_list, move)
        else:
            print("DEPTH: ", depth)
            save_parameters_to_file(board_list, depth, x_l_substr, x_r_range, y_l_substr, y_r_range)
            timer = time.time()
            run_cpp()
            move = get_indexand_print_board_from_file(board_list)
            if time.time() - timer <= 0.05:
                depth = 5
            elif time.time() - timer >= 5:
                depth = 5

        click_mouse(move)

        LAST_4_MOVES.append(move)
        if len(LAST_4_MOVES)>4:
            LAST_4_MOVES.pop(0)
        x_l_substr, x_r_range, y_l_substr, y_r_range = calc_x_y_substractors()

#000000000000000000000000000000000000000000000000000000000000000O0O000000000000O0O000000000000OXXXXOX00000000OXOOOX0000000000000X00000000000000X0000000000000000000000000000000000000000000000000000000000000000000000000000000000