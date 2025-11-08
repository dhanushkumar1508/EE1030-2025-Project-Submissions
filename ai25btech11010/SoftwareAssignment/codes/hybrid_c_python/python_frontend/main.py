import numpy as np
import ctypes
import os
import sys 
import matplotlib.pyplot as plt
from PIL import Image

def load_c_library():
    #the location of shared libary
    lib_name = '../../c_libs/main.so'
    C_LIB = ctypes.CDLL(lib_name)
    c_double_p = np.ctypeslib.ndpointer(dtype=np.float64, ndim=1, flags='C_CONTIGUOUS')
    c_int = ctypes.c_int
    C_LIB.svd_reconstruct.argtypes = [ # input variables list
        c_int,               
        c_int,               
        c_double_p,          
        c_int,               
        c_double_p,          
        ctypes.POINTER(ctypes.c_double) 
    ]
    C_LIB.svd_reconstruct.restype = None
    return C_LIB

def main():
    C_LIB = load_c_library()
    img_paths = ['../../../figs/einstein.jpg','../../../figs/globe.jpg','../../../figs/greyscale.png'] #image address 
    k_values = [5,20, 50, 100, 200] # k values
    plot_dir = '../../../figs'# adress to store images
    
    for img_path in img_paths:# loop for three images
        
        print(f"STARTING PROCESSING FOR IMAGE: {img_path}")
 
        errors = []
        
            
        img_pil = Image.open(img_path).convert('L')# coverting image into matrix

        A_orig = np.array(img_pil, dtype=np.float64)
        m, n = A_orig.shape
        A_orig_flat = A_orig.flatten().copy()#flattening for easy computations 
        
        print(f"Original Image size: {m} x {n}.")
        
        for k in k_values:
            print(f"--- Processing rank k = {k} ---")
            
            A_k_flat = np.zeros(m * n, dtype=np.float64)
            frobenius_error_out = ctypes.c_double(0.0) 
            
            # calling funtion from shared libary of c
            C_LIB.svd_reconstruct(
                m, 
                n, 
                A_orig_flat, 
                k, 
                A_k_flat,
                ctypes.byref(frobenius_error_out) 
            )
            
            final_frobenius_error = frobenius_error_out.value 
            A_k = A_k_flat.reshape(m, n)
            A_k_display = np.clip(A_k, 0, 255).astype(np.uint8)

            errors.append(final_frobenius_error)
            
            print(f"Frobenius Norm Error (k={k}): {final_frobenius_error:.2f}")

            plt.figure(figsize=(5, 5)) 
            plt.imshow(A_k_display, cmap='gray')#coverting matrix to image
            plt.title(f'Reconstructed k={k} (Error: {final_frobenius_error:.0f})')
            plt.axis('off')
            
            base_name, ext = os.path.splitext(os.path.basename(img_path))#extracting base name of image
            save_filename = os.path.join(plot_dir, f'{base_name}_k_{k}.png')
            
            plt.imsave(save_filename, A_k_display, cmap='gray', origin='upper') 
            print(f"Saved reconstructed image: {save_filename}")
            
            plt.show()

            plt.close() 
        
        # plotting k vs error
        plt.figure(figsize=(8, 5))
        plt.plot(k_values, errors, marker='o', linestyle='-', color='r')
        plt.title(f'Frobenius Norm Error vs. Rank (k) for {os.path.basename(img_path)}')
            
        plt.xlabel('Rank k')
        plt.ylabel(r'Frobenius Norm Error $||A - A_k||_F$')
        plt.grid(True)
        
        base_name, ext = os.path.splitext(os.path.basename(img_path))
        error_filename = os.path.join(plot_dir, f'{base_name}_error_vs_k.png')
        
        plt.savefig(error_filename)
        print(f"Saved error plot: {error_filename}")
        
        plt.show()

if __name__ == '__main__':
    main()
