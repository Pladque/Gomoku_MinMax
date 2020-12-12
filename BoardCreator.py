import pyautogui
from PIL import Image
import image_slicer
import glob
import time
import numpy
import pyscreenshot as ImageGrab
from board_coords import *
    
    
    #SS.show()



file_move_from_cpp_r = open("string_index_return.txt", 'r')
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
        print(SS[x,y])

#search board in file_moves_data_r
#calc good depth

#save board and depth to file_board_w
file_board_w.write(board_str)
#run .exe 
#w8 for end
#read file_move_from_cpp_r file
#convert it to coords
#click on right spot on screen


file_board_w.close()
file_moves_data_r.close()
file_move_from_cpp_r.close()
