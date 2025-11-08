#  Truncated SVD Image Compression (C/Python Hybrid)

This project uses a hybrid approach for image compression: the high-performance Singular Value Decomposition (SVD) algorithm is implemented in **C**, and **Python** handles image input/output (I/O) and visualization via `ctypes`.

---

##  Project Structure Map

This structure adheres to the assignment's requirements, showing the location for all source files, the compiled library, and the input/output figures.

SoftwareAssignment/
├── codes/
│   ├── c_libs/
│   │   └── svd_c_lib.so        <-- Compiled C Shared Library (Output of Step 2)
│   └── hybrid_c_python/
│       ├── c_backend/
│       │   └── svd_c_lib.c     <-- C Source Code (SVD Algorithm)
│       └── python_frontend/
│           └── main.py         <-- Python Driver (I/O, Plotting)
└── figs/
    ├── einstein.jpg            <-- Input Image (Place your image here)
    ├── einstein_k_10.png       <-- Reconstructed Images (Output of Step 3)
    ├── einstein_k_50.png       <-- ... and all other k-ranks
    └── einstein_error_vs_k.png <-- Error Plot (Output of Step 3)

---

## How to Run the Project

### Step 1: Place Image

Ensure your target image (e.g., `einstein.jpg`) is placed inside the **`figs/`** directory.

### Step 2: Compile the C Library (Critical Step)

You must compile the C source code into a shared library and save it in the correct location (`codes/c_libs/`).

**Navigate** to the `c_backend/` directory and execute the following command:

```bash
# Execute this command from the: ./codes/hybrid_c_python/c_backend/
gcc -shared -o ../../c_libs/svd_c_lib.so svd_c_lib.c -lm -fPIC
```

###  Step 3 :Execute the Python Script

# Execute this command from the: ./codes/hybrid_c_python/python_frontend/
python3 main.py
