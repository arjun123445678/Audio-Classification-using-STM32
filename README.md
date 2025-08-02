# 🎵 Voice Command Classification on STM32 using NanoEdge AI

This project demonstrates real-time classification of voice commands (3 songs) on the STM32 B-L475E-IOT01A board using the onboard MP34DT01 digital microphone and NanoEdge AI Studio.
<img width="1470" height="889" alt="image" src="https://github.com/user-attachments/assets/a33ebc1d-ff2c-4f9d-981c-17e6c94d3969" />
## 🧠 Project Summary

- 🎙️ Audio captured using the onboard **MP34DT01** PDM mic
- 🧮 Signal digitized using **DFSDM + DMA**
- 🤖 Classification via **NanoEdge AI** model (trained on 3 songs: S1, S2, S3)
- 📤 Output streamed via **UART** to PC for display and plotting
- 📈 Real-time Python script to visualize waveform and FFT

- ## 🛠 Hardware Used

- [x] STM32 B-L475E-IOT01A
- [x] MP34DT01 (on-board mic)
- [x] USART2 UART (for PC display)
- [x] DFSDM1 + DMA (for high-speed audio capture)
## 🧪 NanoEdge AI Studio Testing

<img width="850" height="441" alt="image" src="https://github.com/user-attachments/assets/ae505c97-231b-44c6-9728-dc41f1891d5c" />

**Model trained using:**
- 3 custom audio datasets:  
  - 🎵 S1 (Song 1 sample)  
  - 🎵 S2 (Song 2 sample)  
  - 🎵 S3 (Song 3 sample)  

**Training Details:**
- Total samples per class: ~500
- Feature type: Time domain → Statistical features
- Dataset recorded via **smartphone**, trimmed & augmented
- **Accuracy** achieved: ~90–95% on real-device testing
- Edge AI model exported and integrated as `knowledge.h` and `NanoEdgeAI.c/h`

## 🛠️ What It Does
- Captures microphone audio with DFSDM + DMA
- Classifies audio with a NanoEdge AI model into `S1`, `S2`, `S3`
- Prints prediction and waveform via UART
- Plots waveform live using PySerial + FFT filtering in Python

##Results
UART log on serial monitor:
<img width="662" height="842" alt="image" src="https://github.com/user-attachments/assets/ad191fa0-41a7-4118-9861-dbdba107c1c0" />
<img width="647" height="845" alt="image" src="https://github.com/user-attachments/assets/cc42c623-037a-4f35-955d-ee1c4c1ae096" />


## 🧪 Requirements

### STM32CubeIDE
- STM32 B-L475E-IOT01A board
- NanoEdge AI Studio model trained for 3 songs
- DFSDM, DMA, UART enabled

### Python (for plotting)
```bash
pip install pyserial matplotlib scipy
