                                                                 HZMI-赫兹矩阵创新实验室
# 关于自动标注
## 你是不是还在为标注数据集而发愁！
## 恭喜看见了这个文档

### 在yolov5里面的detect文件里面


def parse_opt():   .....


## 也就是我们平常修改配置的地方
### 我们只需要先手动标注300张左右的高清数据集，进行训练

## 再将训练好的pt文件部署进去

![alt text](https://github.com/random-zhou/HzMi-StudyTime/blob/main/basement/all_image/labelimg_image/labelimg_image1.png)

### 注意！！！这里修改的地方除了原来我们修改的"weight","source","data",还有

![alt text](https://github.com/random-zhou/HzMi-StudyTime/blob/main/basement/all_image/labelimg_image/labelimg_image2.png)

### 这里有两个要注意的地方
#### 1.我们是在原有的基础上加上“ default=True",并没有对原来的部分进行删减
#### 2.我们只可以用对应的pt文件进行标注
#### 比如，你用了yolov5_6.0的版本，就必须用yolov5_6.0的detect.py文件，即使是yolov5_7.0都不行！！！！
