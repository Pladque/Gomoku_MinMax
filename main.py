import image_slicer
import time
import numpy
import pyscreenshot as ImageGrab
from board_coords import *
import subprocess
import os
from subprocess import Popen, PIPE
from termcolor import colored
from pynput.mouse import Button, Controller

# CONFIG SETTINGS #
SS_DIR = str(os.path.dirname(os.path.realpath(__file__))) + "\ss.png"       
EXE_DIR = str(os.path.dirname(os.path.realpath(__file__))) + "\MULTITHREAD tictactoe cpp 15x15.exe"       
BLACK = (40, 40, 40)
WHITE = (243, 243, 243)

AI = BLACK
OPPONENT = WHITE

mouse = Controller()
MOVES_BASE = {}
LAST_4_MOVES = []

# Loading mouse coords for mouse #
f = open("mouseClickPos.txt", 'r')
lines = f.readlines()
CLICK_X_POSITIONS = [int(coord) for coord in lines[0].replace('\n', '').split(" ")]
CLICK_Y_POSITIONS = [int(coord) for coord in lines[1].split(" ")]
f.close()

def get_curr_board(ss_gap:int) ->str:
    time.sleep(ss_gap)
    SS = ImageGrab.grab(bbox=(410,130,963,685))
    SS.save(SS_DIR)

    #creating board
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
    subprocess.check_call([EXE_DIR])

def get_index_from_file(board_list:list):
    file_move_from_cpp_r = open("string_index_return.txt", 'r')
    ind = file_move_from_cpp_r.readline()
    ind = int(ind)
    ind_x = int(ind) %15
    ind_y = int(int(ind) /15)
    print(ind_x, ind_y)
    file_move_from_cpp_r.close()
    board_list[ind_y * 15 + ind_x] = 'X'        

    '''
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
    '''
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
    x_l_substr = min(LAST_4_MOVES[0]%15, LAST_4_MOVES[1]%15, LAST_4_MOVES[2]%15, LAST_4_MOVES[3]%15)
    x_r_substr = max(LAST_4_MOVES[0]%15, LAST_4_MOVES[1]%15, LAST_4_MOVES[2]%15, LAST_4_MOVES[3]%15)
    y_l_substr = int(min(LAST_4_MOVES[0]/15, LAST_4_MOVES[1]/15, LAST_4_MOVES[2]/15, LAST_4_MOVES[3]/15))
    y_r_substr = int(max(LAST_4_MOVES[0]/15, LAST_4_MOVES[1]/15, LAST_4_MOVES[2]/15, LAST_4_MOVES[3]/15))

    x_l_substr -= 6
    x_r_substr += 6
    y_l_substr -= 6
    y_r_substr += 6

    if x_l_substr < 0: x_l_substr = 0
    if x_r_substr > 14: x_r_substr = 14
    if y_l_substr < 0: y_l_substr = 0
    if y_r_substr > 14: y_r_substr = 14

    return x_l_substr, x_r_substr, y_l_substr, y_r_substr

def click_mouse(move:int):
    ind_x= move % 15
    ind_y = int(move / 15)
    mouse.position = (CLICK_X_POSITIONS[ind_x],CLICK_Y_POSITIONS[ind_y])
    mouse.click(Button.left, 1)

def read_postions_to_click():
    f = open("mouseClickPos.txt", 'r')

    lines = f.readlines()
    CLICK_X_POSITIONS = [int(coord) for coord in lines[0].replace('\n', '').split(" ")]
    CLICK_Y_POSITIONS = [int(coord) for coord in lines[1].split(" ")]

    f.close()

if __name__ == '__main__':
    create_moves_base()
    read_postions_to_click()
    board_list = []
    x_l_substr, x_r_range, y_l_substr, y_r_range =  0, 14, 0, 14
    depth = 5
    turn_counter = 0
    
    while True:
        turn_counter += 1
        temp_board_str = get_curr_board(1)
        if temp_board_str == "-1":
            break

        # waiting for opponent move #
        while ''.join(board_list) == temp_board_str:
            temp_board_str = get_curr_board(1)
            time.sleep(0.1)

        board_list = list(temp_board_str)
        move = 0

        # making move from database (if present)
        if ''.join(board_list) in MOVES_BASE.keys():
            move = MOVES_BASE[''.join(board_list)]
            print_curr_board(board_list, move)
        #calculating best move
        else:
            print("DEPTH: ", depth)
            save_parameters_to_file(board_list, depth, x_l_substr, x_r_range, y_l_substr, y_r_range)
            timer = time.time()
            run_cpp()
            move = get_index_from_file(board_list)
            if time.time() - timer <= 0.06:
                depth = 7
            elif time.time() - timer >= 3:
                depth = 5

        click_mouse(move)
        #calculating substractors
        LAST_4_MOVES.append(move)
        if len(LAST_4_MOVES)>4:
            LAST_4_MOVES.pop(0)
            x_l_substr, x_r_range, y_l_substr, y_r_range = calc_x_y_substractors()
        else:
            x_l_substr, x_r_range, y_l_substr, y_r_range = 0,14,0,14

        if turn_counter % 5 == 0:   #bc I want sometimes to check all board
            depth = 5
            print(colored("DEPTH: ", 'green'), end = '')
            print(colored(depth, 'green'))
            x_l_substr, x_r_range, y_l_substr, y_r_range = 0,14,0,14
        
        board_list[move] = 'X'