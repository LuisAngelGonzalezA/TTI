class cerrar_select:
	def __init__(self, parent):
		self.parent = parent
		self.parent.protocol("WM_DELETE_WINDOW", self.on_closing)

	def on_closing(self):
		print("Se elmino")
		self.parent.destroy()