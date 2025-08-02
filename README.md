This project classifies 3 different songs in real-time using:
- STM32 B-L475E-IOT01A board
- On-board MP34DT01 PDM microphone
- NanoEdge AI Studio model
- Real-time UART plotting via Python

## 🛠️ What It Does
- Captures microphone audio with DFSDM + DMA
- Classifies audio with a NanoEdge AI model into `S1`, `S2`, `S3`
- Prints prediction and waveform via UART
- Plots waveform live using PySerial + FFT filtering in Python
<img width="1470" height="889" alt="image" src="https://github.com/user-attachments/assets/a33ebc1d-ff2c-4f9d-981c-17e6c94d3969" />
##Results
![WhatsApp Image 2025-08-02 at 12 14 44_5c6d9e2f](https://github.com/user-attachments/assets/2bf6c06d-f50f-47b3-b0f2-9b00bb6ab9ba)
![WhatsApp Image 2025-08-02 at 12 14 44_c38cd782](https://github.com/user-attachments/assets/dfafed59-837e-4033-9208-14cd63cef89a)





## 📦 Folder Overview
- `Core/`: STM32CubeIDE project files
- `NEAI_Lib/`: NanoEdge AI Studio exported model
- `python_plot/`: Real-time waveform plot script

## 🧪 Requirements

### STM32CubeIDE
- STM32 B-L475E-IOT01A board
- NanoEdge AI Studio model trained for 3 songs
- DFSDM, DMA, UART enabled

### Python (for plotting)
```bash
pip install pyserial matplotlib scipy
