from pynput.mouse import Controller, Button
from pynput.mouse import Listener

mouse = Controller()

MOUSE_POS_X = ""
MOUSE_POS_Y = ""
f = open("mouseClickPos.txt", 'w')

def on_move(x, y):
    #print('Pointer moved to {0}'.format(
    #    (x, y)))
    pass

def on_click(x, y, button, pressed):
    
    if pressed:
        f.write(str(y))
        f.write(" ")
    print('{0} at {1}'.format(
        'Pressed' if pressed else 'Released',
        (x, y)))
    
    if not pressed:
        # Stop listener
        return False

def on_scroll(x, y, dx, dy):
    return False
    


while True:
    with Listener(
            on_move=on_move,
            on_click=on_click,
            on_scroll=on_scroll) as listener:
        listener.join()

f.close()



