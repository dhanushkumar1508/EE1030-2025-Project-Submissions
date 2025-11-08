# Image Compression Using Truncated SVD

## Overview
This project implements **Image Compression using Truncated Singular Value Decomposition (SVD)**. 
The goal is to approximate a grayscale image matrix by retaining only the top `k` singular values and corresponding singular vectors. 
This reduces the amount of data required to represent the image while preserving most of its important visual information.

The algorithm uses the **Power Iteration with Deflation** method to iteratively compute the top singular values and vectors, avoiding the computational cost of a full SVD. 
It demonstrates how mathematical concepts from linear algebra can be applied to real-world applications like image compression.

---

## Key Features
- **Truncated SVD implementation** for image compression. 
- **Power Iteration with Deflation** used to compute top `k` singular values. 
- **C + Python hybrid structure** for efficiency. 
- Supports large grayscale images.  
- Computes and reports **Frobenius norm error** (`‖A - A_k‖_F`). 
- Generates **plots of k vs error** to visualize reconstruction accuracy. 
- Saves reconstructed images and error tables for multiple ranks.

---

## Folder Structure
├── Software/
│ ├── codes/
│ │ ├── main.py # Python driver code
│ │ ├── svd_power.c # C implementation of Power Iteration
│ │ ├── svd_power.h # Header file
│ │ ├── Makefile # For building shared library
│ │ └── utils.py # Helper functions for image I/O
│ ├── figs/ # Original and reconstructed images, plots
│ ├── tables/ # Tables of Frobenius norm error
│ └── report/ # LaTeX report source
└── README.md
