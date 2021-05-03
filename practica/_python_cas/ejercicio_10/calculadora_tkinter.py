import tkinter as tk

root = tk.Tk()

# Definir variables
var_operation = tk.StringVar()
var_operation.set('z_1 + z_2 = ')
var_result = tk.StringVar()
var_result.set('Resultado')

# Definir etiquetas
re1_label = tk.Label(text='Re(z_1) = ')
im1_label = tk.Label(text='Im(z_1) = ')
re2_label = tk.Label(text='Re(z_2) = ')
im2_label = tk.Label(text='Im(z_2) = ')

# Definir entradas
re1 = tk.Entry(root)
im1 = tk.Entry(root)
re2 = tk.Entry(root)
im2 = tk.Entry(root)


# Definir comando suma
def sumar_entradas():
    re1_user = re1.get()
    im1_user = im1.get()
    re2_user = re2.get()
    im2_user = im2.get()
    
    re_result = float(re1_user) + float(re2_user)
    im_result = float(im1_user) + float(im2_user)
    
    text_result = f"{re_result} + i {im_result})"
    
    var_result.set(text_result)

    z_1 = f'{re1_user} + i {im1_user}'
    z_2 = f'{re2_user} + i {im2_user}'
    text_operation = f'({z_1}) + ({z_2}) = '
    var_operation.set(text_operation)

# Definir boton para el comando
sum_button = tk.Button(root,
                     text='Calcular suma',
                     command=sumar_entradas)
# Definir etiqueta para la operacion
sum_operation = tk.Label(root,
                         textvariable=var_operation)

# Definir etiqueta para el resultado
sum_result = tk.Label(root,
                    textvariable=var_result)


# Mostrar los objetos en pantalla, en una grilla
re1_label.grid(row=0, column=0)
re1.grid(row=0, column=1)
im1_label.grid(row=0, column=2)
im1.grid(row=0, column=3)

re2_label.grid(row=1, column=0)
re2.grid(row=1, column=1)
im2_label.grid(row=1, column=2)
im2.grid(row=1, column=3)

sum_button.grid(row=2, column=0)
sum_operation.grid(row=2, column=1)
sum_result.grid(row=2, column=2)

root.mainloop()
