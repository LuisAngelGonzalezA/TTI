from tkinter import *
import tkinter as Tk
from tkinter import ttk
import tkinter.font as tkFont
class Table(Tk.Frame):
    def __init__(self, parent=None, title="", headers=[], height=5, *args, **kwargs):
        Tk.Frame.__init__(self, parent, *args, **kwargs)
        self._title = Tk.Label(self, text=title, background="green", font=("Helvetica", 16))
        self._headers = headers
        self._tree = ttk.Treeview(self,
                                  height=height,
                                  columns=self._headers, 
                                  show="headings")
        self._title.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)

        # Agregamos dos scrollbars 
        vsb = ttk.Scrollbar(self, orient="vertical", command=self._tree.yview)
        vsb.pack(side='right', fill='y')
        hsb = ttk.Scrollbar(self, orient="horizontal", command=self._tree.xview)
        hsb.pack(side=BOTTOM, fill=BOTH, expand=True,padx=5, pady=5)

        self._tree.configure(xscrollcommand=hsb.set, yscrollcommand=vsb.set)
        self._tree.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)

        for header in self._headers:
            self._tree.heading(header, text=header.title())
            self._tree.column(header, stretch=True,
                              width=tkFont.Font().measure(header.title()))

    def add_row(self, row):
        self._tree.insert('', 'end', values=row)
        for i, item in enumerate(row):
            col_width = tkFont.Font().measure(item)
            if self._tree.column(self._headers[i], width=None) < col_width:
                    self._tree.column(self._headers[i], width=col_width)