from Tkinter import *
import tkMessageBox

root = Tk()


def helloCallBack():
   
   print voltaje_ingresado.get(),"\n"
   voltaje_ingresado.delete(0,END)
   print volateje_deseado.get(),"\n"
   volateje_deseado.delete(0,END)
   type(voltaje_ingresado)
   
   	











root.title('formulario 1')
# row 1 : the name
nombre_label = Label(root,text="Voltaje ingresado :")
nombre_label.grid(row=1,column=1)
nombre_str = StringVar()
voltaje_ingresado = Entry(root,textvariable=nombre_str)
voltaje_ingresado.grid(row=1,column=2)
#row 2 : the last name
last_label= Label(root,text="Voltaje deseado : ")
last_label.grid(row=2,column=1)
last_str = StringVar()
volateje_deseado = Entry(root,textvariable=last_str)
volateje_deseado.grid(row=2,column=2)

#row 4 : end
finish = Button(root,text ="Hello", command = helloCallBack)
finish.grid(row=4,column=2)
root.mainloop()