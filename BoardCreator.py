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

# TODO
# changable if AI is black or opponent is black
# fix board evaluation in .cpp bc now it consider fe XOOOOX as -4 :)


file_moves_data_r = open("calculated_moves.txt", 'r')
file_board_w = open("board.txt", 'w')

#make ss
time.sleep(0)
SS = ImageGrab.grab(bbox=(410,130,963,685))
SS.save("D:\Projects\PythonProjects\PrivateGithub\Tic-Tac-Toe_MinMax\ss.png")

#find white and balck
#create board
SS = ImageGrab.grab(bbox=(410,130,963,685)).load()
board_str = ""
for y in FIELD_Y:
    for x in FIELDS_X:
        if SS[x,y] == (243, 243, 243):
            board_str += 'O'
        elif SS[x,y] == (40, 40, 40):
            board_str += 'X'
        else:
            board_str+='0'

#search board in file_moves_data_r
move = 0
for line in file_moves_data_r.readlines():
    if  board_str == line[:line.index(';')].replace(' ', ''):
        move = int(line[line.index(';')+1:].replace(' ', '').replace('\n', ''))
        break
file_moves_data_r.close()

#calc good depth
depth = 5  #temp

# Find good square
left_x_substr, right_x_substr, left_y_substr, right_y_substr = 0,14,0,14    #temp

#save board and depth to file_board_w
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

#run .exe 
subprocess.check_call(['D:\Projects\PythonProjects\PrivateGithub\Tic-Tac-Toe_MinMax\MULTITHREAD tictactoe cpp 15x15.exe'])
#o = subprocess.Popen(['cmd','/c',r'D:\Projects\PythonProjects\PrivateGithub\Tic-Tac-Toe_MinMax\EXE\MULTITHREAD tictactoe cpp 15x15.exe'])
#o.wait()  

#w8 for end
file_move_from_cpp_r = open("string_index_return.txt", 'r')
ind = file_move_from_cpp_r.readline()
ind_x = int(ind) %15
ind_y = int(int(ind) /15)
print(ind_x, ind_y)
file_move_from_cpp_r.close()
#read file_move_from_cpp_r file
#convert it to coords
#click on right spot on screen


