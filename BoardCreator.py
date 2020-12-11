import pyautogui
from PIL import Image
import image_slicer
import glob

def takeScreenshot ():
    
    myScreenshot = pyautogui.screenshot()
    myScreenshot.save(r"D:\Projects\PythonProjects\PrivateGithub\Tic-Tac-Toe_MinMax\ss.png")



file_move_from_cpp_r = open("string_index_return.txt", 'r')
file_moves_data_r = open("calculated_moves.txt", 'r')
file_board_w = open("board.txt", 'w')

#make ss
takeScreenshot ()
#find white and balck
#create board
#search board in file_moves_data_r
#calc good depth
#save board and depth to file_board_w
#run .exe 
#w8 for end
#read file_move_from_cpp_r file
#convert it to coords
#click on right spot on screen


file_board_w.close()
file_moves_data_r.close()
file_move_from_cpp_r.close()
