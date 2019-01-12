from tkinter import *
from tkinter.ttk import *

class myFrame:
    def __init__(self, master):
        s = Style()
        s.configure('My.TFrame', background='#555555')
        master = Frame(master, style='My.TFrame')
        master.place(x=0, y=0, width=1027, height=768)

        lblName = Label(master, text="OK")
        lblName.place(x=10, y=10, width=100, height=30)


def main():
    root = Tk()
    root.geometry("1024x768+100+100")
    app = myFrame(root)
    root.mainloop()

#if __name__ == '__main__':
#    main()