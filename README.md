# HzMi-StudyTime

![alt text](basement/all_image/md_image/md_image1.png)

# 链接直通车
### Basement
|basement            |related information                                                                                                                                                                                  |
|--------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|Linux               |[Linux](https://github.com/random-zhou/HzMi-StudyTime/blob/main/basement/Linux%E5%9F%BA%E7%A1%80%E6%93%8D%E4%BD%9C%E6%95%99%E5%AD%A6.md)                                                             |                                                                       
|Git                 |[Git](https://github.com/random-zhou/HzMi-StudyTime/blob/main/basement/git%E5%9F%BA%E7%A1%80%E6%93%8D%E4%BD%9C%E6%95%99%E5%AD%A6.md)                                                                 |                                                                       
|Markdown            |[Markdown](https://github.com/random-zhou/HzMi-StudyTime/blob/main/basement/markdown%E5%9F%BA%E7%A1%80%E6%93%8D%E4%BD%9C%E6%95%99%E5%AD%A6.md)                                                       |                                                                     
|Python              |[Python](https://github.com/random-zhou/HzMi-StudyTime/blob/main/basement/Python%E5%9F%BA%E7%A1%80%E6%95%99%E5%AD%A6.md)                                                                             |                                                                       
|C                   |[C](https://github.com/random-zhou/HzMi-StudyTime/blob/main/basement/C%E8%AF%AD%E8%A8%80%E5%9F%BA%E7%A1%80%E6%95%99%E5%AD%A6.md)                                                                     |                                                                       
|C++                 |[C++](https://github.com/random-zhou/HzMi-StudyTime/blob/main/basement/C%2B%2B%E8%AF%AD%E8%A8%80%E5%9F%BA%E7%A1%80%E6%95%99%E5%AD%A6.md)                                                             |                                                                       
|                    |                                                                                                                                                                                                     |                                                                       
|                    |                                                                                                                                                                                                     |                                                                       
|                    |                                                                                                                                                                                                     |                                                                       
### MCU 
|brand_name       |related information            |
|------------------|-------------------------------| 
|stm32f1-series   |                               |
|stm32f4-series                  |                               |
|stm32f7-series              |                                        |
|stm32g4-series              |                               |                                                                  
|stm32h7-series             |                               |
|cw32                  |                               |
|                  |                               |
|TC264                  |                               |
|                  |                               |
|                  |                               |
|                  |                               |
|wch32                  |                               |
|                  |                               |
|stc32                  |                               |
|                  |                               |
|                  |                               |

### Module

|module              |related information                                   |code_example(stm32f103-series,stm32f407-series,stm32f427-series,stm32h743-series,stm32h750-series)                                                           |
|--------------------|------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------|
|tb6612              |                                                      |                                                                                                                                                             |
|mpu6050             |                                                      |                                                                       |
|mpu9250             |                                                      |                                                                       |
|oled_iic            |                                                      |                                                                       |
|lcd                 |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |

### control_algorithm

|control_algorithm                      |related information                                   |code_example(C or CPP)                                                           |
|---------------------------------------|------------------------------------------------------|---------------------------------------------------------------------------------|
|PID                                    |                                                      |[PID_c_best],[PID_h_best];[PID1_c](usual_control_algorithm/PID1.c),[PID1_h](usual_control_algorithm/PID1.h);[PID2_c],[PID2_h]；                                                     |
|MPC                                    |                                                      |[MPC_c_best],[MPC_h_best];[MPC1_c],[MPC1_h];[MPC2_c],[MPC2_h]；                                                                      |
|LQR                                    |                                                      |[LQR_c_best]，[LQR_h_best];[LQR1_c],[LQR1_h];[LQR2_c],[LQR2_h]；                                                                       |
|Kalman_filter(卡尔曼滤波)               |                                          |[Kalman_filter_c_best]，[Kalman_filter_h_best];[kalman_filter1_c](usual_control_algorithm/Kalman.c),[kalman_filter1_h](usual_control_algorithm/Kalman.h);[kalman_filter2_c],[kalman_filter1_h]； |
|Quaternion(四元素陀螺仪解算)            |                                                      |[Quaternion_c_best]，[Quaternion_h_best];[Quaternion1_c](usual_control_algorithm/Quaternion1.c),[Quaternion1_h](usual_control_algorith/Quaternion1.h);[Quaternion2_c],[Quaternion2_h]；|
|losspass_filter(低通滤波)               |                                                      |[lowpass_filter_c_best],[lowpass_filter_h_best];[lowpass_filter1_c](usual_control_algorithm/lowpass_filter1.c),[lowpass_filter1_h](usual_control_algorithm/lowpass_filter1.h);[lowpass_filter2_c],[lowpass_filter2_h]                                                     |
|                                       |                                                      |                                                                       |
|                                       |                                                      |                                                                       |
|                                       |                                                      |                                                                       |






### Computer-Vision
|model                                                             |Paper                                                                                                                                  |                   CODE                                               |
|------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------|
|YOLO-series                                                       |[YOLOv1](Paper/YOLOv1.pdf);[YOLOv2](Paper/YOLOv2.pdf);[YOLOv3](Paper/YOLOv3.pdf);[YOLOv4](Paper/YOLOv4.pdf);[YOLOv5](Paper/YOLOv5.pdf);|[YOLOv1];[YOLOv2](https://github.com/longcw/yolo2-pytorch);[YOLOv3](https://github.com/ultralytics/yolov3);[YOLOv4](https://github.com/Tianxiaomo/pytorch-YOLOv4);[YOLOv5](https://github.com/ultralytics/yolov5);                |           
|                                                                  |[YOLOv6];[YOLOv7];[YOLOv8];[YOLOv9];                                                                                                   |[YOLOv6](https://github.com/meituan/YOLOv6);[YOLOv7](https://github.com/WongKinYiu/yolov7);[YOLOv8](https://github.com/ultralytics/ultralytics);[YOLOv9](https://github.com/WongKinYiu/yolov9);[YOLOv5lite](https://github.com/ppogg/YOLOv5-Lite)                                   |
|Resnet(Deep Residual Learning for Image Recognition)              |[Resnet](Paper/Resnet.pdf);                                                                                                            |[Resnet](https://github.com/ry/tensorflow-resnet);                                                              | 
|RDN(Residual Dense Network for Image Super-Resolution)            |[RDN](Paper/RDN.pdf);                                                                                                                  |[RDN](https://github.com/yulunzhang/RDN);                                                                 | 
|ELC(Efficient Layer Compression Without Pruning)                  |[ELC](Paper/Efficient%20Layer%20Compression%20Without%20Pruning.pdf);                                                                  |[ELC];                                                                 | 
|GhostSR(GhostSR: Learning Ghost Features for Efficient Image Super-Resolution)|[GhostSR](Paper/GhostSR.pdf)                                                                                               |[GhostSR]                                                              | 
|CNN(Gradient-Based Learning Applied to Document Recognition)      |[CNN](Paper/CNN.pdf)                                                                                                                   |[CNN]                                                                       | 
|RCNN(Rich feature hierarchies for accurate object detection and semantic segmentation)|[RCNN](Paper/R-CNN.pdf)                                                                                            |[RCNN]                                                                       | 
|Fast R-CNN                                                        |[Fast_R-CNN](Paper/Fast%20R-CNN.pdf)                                                                                                   |[Fast_R-CNN]                                                           | 
|Faster R-CNN(Towards Real-Time Object Detection with Region Proposal Networks)|[Faster_R-CNN](Paper/Faster%20R-CNN.pdf)                                                                                   |[Faster_R-CNN]                                                         | 
|DPM(Object Detection with Discriminatively Trained Part Based Models)|[DPM](Paper/DPM.pdf)                                                                                                                |[DPM]                                                                       | 
|Mark R-CNN                                                        |[Mark R-CNN](Paper/Mask%20R-CNN.pdf)                                                                                                   |[Mark_R-CNN]                                                        | 
|Vision Transformer( AN IMAGE IS WORTH 16X16 WORDS: TRANSFORMERS FOR IMAGE RECOGNITION AT SCALE)|[Vision_Transformer](Paper/VisionTransformer.pdf)                                                         |[Vision_Transformer]                                                | 
|Unet(Convolutional Networks for Biomedical Image Segmentation)    |[Unet](Paper/U-Net.pdf)                                                                                                                |[Unet]                                                                       | 
|DETR(End-to-End Object Detection with Transformers)               |[DETR](Paper/DETR.pdf)                                                                                                                 |[DETR]                                                                       | 
|                                                                  |                                                                                                                                       |                                                                       | 
|                                                                  |                                                                                                                                       |                                                                       | 
|                                                                  |                                                                                                                                       |                                                                       | 
|                                                                  |                                                                                                                                       |                                                                       | 
|                                                                  |                                                                                                                                       |                                                                       | 
|                                                                  |                                                                                                                                       |                                                                       | 
|                                                                  |                                                                                                                                       |                                                                       | 
|                                                                  |                                                                                                                                       |                                                                       | 
|                                                                  |                                                                                                                                       |                                                                       | 

### Large-Language-Model
|model               |Paper                                                 |                   CODE                                             |
|--------------------|------------------------------------------------------|-----------------------------------------------------------------------|
|Transformer         |[Transformer](Paper/Transfomer.pdf)                   |[Transformer]                                                          |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |
|                    |                                                      |                                                                       |

### 项目推广
### API-Studio
[API-Studio](https://github.com/random-zhou/API-Studio)