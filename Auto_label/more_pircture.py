#coding=utf-8
#图像处理脚本
#翻转
#放缩
#旋转
#平移
#剪切
#调节亮度
#调节对比度
#调节饱和度
#调节色调
#高斯滤波
#指数滤波
#中值滤波
#对数滤波

import cv2
import numpy as np  
import matplotlib.pyplot as plt  
import os  
from math import cos, sin, radians  
import random



 
#翻转
def overturn(input_folder, output_folder):  
    #这段代码首先检查 output_folder 是否存在。如果不存在，它会创建这个文件夹。
    if not os.path.exists(output_folder):  
        os.makedirs(output_folder)  
    
    #使用 os.listdir 函数列出 input_folder 中的所有文件和文件夹。
    image_files = [f for f in os.listdir(input_folder) if f.endswith('.jpg') or f.endswith('.png')]  

    for i,filename in enumerate(image_files):  
        
        try: 
            img = cv2.imread(os.path.join(input_folder, filename))  
            if img is None:  
                print(f"无法读取文件 {filename}")  
                continue  
            
            flip_img_0 = cv2.flip(img,0 )#垂直翻转  
            flip_img_1 = cv2.flip(img,1 )#水平翻转
            flip_img_01 = cv2.flip(img,-1 )#垂直加水平
            # 生成唯一的输出文件名  
            base_name, _ = os.path.splitext(filename) 
            output_path_0 = os.path.join(output_folder, f'{base_name}_overturn_0.jpg')  
            output_path_1 = os.path.join(output_folder, f'{base_name}_overturn_1.jpg')  
            output_path_01 = os.path.join(output_folder, f'{base_name}_overturn_01.jpg')  

            cv2.imwrite(output_path_0, flip_img_0)
            cv2.imwrite(output_path_1, flip_img_1)
            cv2.imwrite(output_path_01, flip_img_01)
            print(output_path_0)
            print(output_path_1)
            print(output_path_01)
        except Exception as e:  
            print(f"处理图片 {filename} 时发生异常: {e}")  
            
            






#放缩 
def resize_images(input_folder, output_folder):  
    #fx 和 fy：缩放因子，分别用于图片的宽度和高度
    # 检查输出文件夹是否存在，如果不存在则创建  
    if not os.path.exists(output_folder):  
        os.makedirs(output_folder)  
  
    image_files = [f for f in os.listdir(input_folder) if f.endswith('.jpg') or f.endswith('.png')]  
    # 遍历指定文件夹中的所有图片文件  
    for i, image_file in enumerate(image_files):  
        try:  
            # 打开图片文件  
            img_path = os.path.join(input_folder, image_file)  
            img = cv2.imread(img_path)  
              
            if img is None:  
                print(f"无法读取文件 {image_file}")  
                continue  
            for i in np.arange(0.5, 1.0, 0.1):
                # 获取图片的高度、宽度和通道数  
                original_height, original_width, channels = img.shape  
                
                # 计算新的尺寸
                new_width = int(original_width *i)  
                new_height = int(original_height *i)  
    
                # 进行尺寸调整  
                resized = cv2.resize(img, (new_width, new_height), interpolation=cv2.INTER_AREA)  

                background = np.zeros_like(img)
                top_left = ((background.shape[1] - resized.shape[1]) // 2, (background.shape[0] - resized.shape[0]) // 2)
                background[top_left[1]:top_left[1] + resized.shape[0], top_left[0]:top_left[0] + resized.shape[1]] = resized

                
                # 创建输出文件路径，添加图片编号和后缀  
                base_name, _ = os.path.splitext(image_file)  
                output_path = os.path.join(output_folder, f'{base_name}_resized_{i:.2f}.jpg')  
                print(output_path)
                # 保存处理后的图片
                cv2.imwrite(output_path, background)  
            for j in np.arange(1.1, 1.6, 0.1):
                width = int(img.shape[1] * j)  
                height = int(img.shape[0] * j)  
                dim = (width, height)  
                enlarged = cv2.resize(img, dim, interpolation=cv2.INTER_LINEAR)  
                
                target_width = img.shape[1]    
                target_height = img.shape[0]  
                
                # 计算需要剪切的部分  
                start_x = (enlarged.shape[1] - target_width) // 2  
                start_y = (enlarged.shape[0] - target_height) // 2  
                end_x = start_x + target_width  
                end_y = start_y + target_height  
                
                # 剪切图片  
                cropped_img = enlarged[start_y:end_y, start_x:end_x]  
                base_name, _ = os.path.splitext(image_file)  
                output_path = os.path.join(output_folder, f'{base_name}_resized_{j:.2f}.jpg')  
                print(output_path)
                # 保存处理后的图片
                cv2.imwrite(output_path, cropped_img)
        except Exception as e:  
            print(f"处理图片 {image_file} 时发生异常: {e}")  


  



#旋转
def pad(img, top, bottom, left, right):  
    pad_img = cv2.copyMakeBorder(img, top, bottom, left, right, cv2.BORDER_CONSTANT, value=0)  
    '''
    src输入图像。
    top顶部边界的大小。
    bottom底部边界的大小。
    left左侧边界的大小。
    right右侧边界的大小。 
    '''
    #边界类型，这里指定为cv2.BORDER_CONSTANT，表示使用常数填充边界。
    return pad_img  
def rotate_images(input_folder, output_folder):  
    # 检查目标文件夹是否存在，如果不存在则创建  
    if not os.path.exists(output_folder):  
        os.makedirs(output_folder)  
    
    image_files = [f for f in os.listdir(input_folder) if f.endswith('.jpg') or f.endswith('.png')]  
    # 遍历指定文件夹中的所有图片文件  
    for i, image_file in enumerate(image_files):  
        try:  
            # 打开图片文件  
            img_path = os.path.join(input_folder, image_file)  
            img = cv2.imread(img_path)  
              
            if img is None:  
                print(f"无法读取文件 {image_file}")  
                continue  
            height, width, channel = img.shape
            # 计算图片中心点  
            cx = int(width / 2)  
            cy = int(height / 2)  
            center = (cx+cy, cy+cx)  
            pad_img = pad(img, cx, cx, cy, cy)  
            height, width, channel = pad_img.shape
            new_dim = (width, height) #新的中心点
  
            # 对每个角度进行旋转操作 
            angles=[45,90,135,180,225,270,315]
            rotated_images = []  
            for angle in angles:
                # 获取旋转矩阵  
                M = cv2.getRotationMatrix2D(center=center, angle=angle, scale=1.0)  
                # 进行仿射变换  
                rotated = cv2.warpAffine(pad_img, M, new_dim)  
                # 添加到旋转后的图片列表中  
                rotated_images.append(rotated)  
  
            # 将旋转后的图片保存到目标文件夹中  
            for i, rotated in enumerate(rotated_images):  
                # 获取原文件名，不包含后缀名  
                base_filename,_ = os.path.splitext(image_file) 
                # 生成新的文件名，包含旋转角度后缀名  
                output_filename = f"{base_filename}_rotate_images{angles[i]}.jpg"  
                output_path = os.path.join(output_folder, output_filename)  
                cv2.imwrite(output_path, rotated)  
                print(output_path)  
        except Exception as e:  
            print(f"Error processing {img_path}: {str(e)}")

#平移
def translation_img(input_folder, output_folder):  
    # 检查输出文件夹是否存在，如果不存在则创建  
    if not os.path.exists(output_folder):  
        os.makedirs(output_folder)  
  
    # 获取输入文件夹中的所有图片文件  
    image_files = [f for f in os.listdir(input_folder) if f.endswith('.jpg') or f.endswith('.png')]  
    
    # 对每个图片文件进行处理  
    for i, image_file in enumerate(image_files):  
        try:  
            # 打开图片文件  
            img_path = os.path.join(input_folder, image_file)  
            img = cv2.imread(img_path)  
              
            if img is None:  
                print(f"无法读取文件 {image_file}")  
                continue  
            rows, cols = img.shape[:2] 
            tx=0
            ty=0
            for i in range(-100,120,20):
                if i==0:
                    continue
                tx=i
                M = np.float32([[1, 0, tx], [0, 1, ty]])  
                dst = cv2.warpAffine(img, M, (cols, rows))  
                
                base_name, _ = os.path.splitext(image_file)  
                output_path = os.path.join(output_folder, f'{base_name}translation_{tx}_{ty}.jpg')  
                # 保存处理后的图片
                cv2.imwrite(output_path,dst )  
            tx=0
            for j in range(-100,120,20):
                if j==0:
                    continue
                ty=j
                M = np.float32([[1, 0, tx], [0, 1, ty]])  
                dst = cv2.warpAffine(img, M, (cols, rows))  
                base_name, _ = os.path.splitext(image_file)  
                output_path = os.path.join(output_folder, f'{base_name}translation_{tx}_{ty}.jpg')  
                # 保存处理后的图片
                cv2.imwrite(output_path,dst ) 
                print(output_path)
        except Exception as e:  
            print(f"处理图片 {image_file} 时发生异常: {e}")  





#剪切
def random_crop(img, crop_ratio=(0.4,0.9), crop_times=5):
    """对图片进行随机裁剪。"""
    '''
    img 表示输入的图片,crop_ratio 是一个元组
    表示裁剪比率范围,crop_times 表示裁剪次数
    '''
    cropped_imgs = []
    height, width, _ = img.shape
    min_ratio, max_ratio = crop_ratio
    '''
    函数返回裁剪后的图片列表。在函数内部，
    首先创建了一个空列表 cropped_imgs 用于存储裁剪后的图片。
    然后获取输入图片的高度和宽度，并从 crop_ratio 元组中获取裁剪比率的最小值和最大值
    '''
    
    for _ in range(crop_times):
        crop_w = random.randint(int(width * min_ratio), int(width * max_ratio))
        crop_h = random.randint(int(height * min_ratio), int(height * max_ratio))

        x = random.randint(0, width - crop_w)
        y = random.randint(0, height - crop_h)

        cropped_img = img[y:y+crop_h, x:x+crop_w]
        cropped_imgs.append(cropped_img)

    return cropped_imgs

def shear(input_folder, output_folder):
    """遍历文件夹中的所有文件，并对每个文件执行随机裁剪操作。"""
    # 检查输出文件夹是否存在，如果不存在则创建  
    if not os.path.exists(output_folder):  
        os.makedirs(output_folder)  
  
    # 获取输入文件夹中的所有图片文件  
    image_files = [f for f in os.listdir(input_folder) if f.endswith('.jpg') or f.endswith('.png')]  
    
    # 对每个图片文件进行处理  
    for i, image_file in enumerate(image_files):  
        try:  
            # 打开图片文件  
            img_path = os.path.join(input_folder, image_file)  
            img = cv2.imread(img_path)  
              
            if img is None:  
                print(f"无法读取文件 {image_file}")  
                continue  
    
            cropped_imgs = random_crop(img)

            for i, cropped_img in enumerate(cropped_imgs):
                base_filename, ext = os.path.splitext(image_file)
                output_filename = f"{base_filename}shear_{i}.jpg"
                output_path = os.path.join(output_folder, output_filename)
                cv2.imwrite(output_path, cropped_img)
                print(output_path)

        except Exception as e:  
                    print(f"处理图片 {image_file} 时发生异常: {e}")  


#调节亮度
def brightness(input_folder, output_folder):
    if not os.path.exists(output_folder):  
        os.makedirs(output_folder)  
  
    # 获取输入文件夹中的所有图片文件  
    image_files = [f for f in os.listdir(input_folder) if f.endswith('.jpg') or f.endswith('.png')]  
    
    # 对每个图片文件进行处理  
    for i, image_file in enumerate(image_files):  
        try:  
            # 打开图片文件  
            img_path = os.path.join(input_folder, image_file)  
            img = cv2.imread(img_path)  
              
            if img is None:  
                print(f"无法读取文件 {image_file}")  
                continue  
            #factor = random.uniform(0,2)
            factors=[0.4,0.6,0.8,1.2]
            for factor in factors:
                table = np.array([i*factor for i in np.arange(0, 256)]).clip(0,255).astype(np.uint8)
                img1 = cv2.LUT(img, table)
                base_name, _ = os.path.splitext(image_file)  
                output_path = os.path.join(output_folder, f'{base_name}brightness_{factor}.jpg')  
                # 保存处理后的图片
                cv2.imwrite(output_path, img1) 
                print(output_path) 
        except Exception as e:  
            print(f"处理图片 {image_file} 时发生异常: {e}")  


#调节对比度
def Histogram_averaging(input_folder, output_folder):  
    # 检查输出文件夹是否存在，如果不存在则创建  
    if not os.path.exists(output_folder):  
        os.makedirs(output_folder)  
  
    # 获取输入文件夹中的所有图片文件  
    image_files = [f for f in os.listdir(input_folder) if f.endswith('.jpg') or f.endswith('.png')]  
    
    # 对每个图片文件进行处理  
    for i, image_file in enumerate(image_files):  
        try:  
            # 打开图片文件  
            img_path = os.path.join(input_folder, image_file)  
            img = cv2.imread(img_path,1)
            
            if img is None:  
                print(f"无法读取文件 {image_file}")  
                continue  
             
            b, g, r = cv2.split(img)  
            # 对每个通道进行直方图均衡化  
            b_eq = cv2.equalizeHist(b)  
            g_eq = cv2.equalizeHist(g)  
            r_eq = cv2.equalizeHist(r)  
            clahe = cv2.createCLAHE (clipLimit = 2.0, tileGridSize=(10, 10))  #对图像进行分割，10*10
            b_pha=clahe.apply(b)
            g_pha=clahe.apply(g)
            r_pha=clahe.apply(r)
            
            # 合并均衡化后的通道  
            img1 = cv2.merge((b_eq, g_eq, r_eq))  
            img2=cv2.merge((b_pha,g_pha,r_pha))

            # 创建输出文件路径，添加图片编号和后缀  
            base_name, _ = os.path.splitext(image_file)  
            output_path1 = os.path.join(output_folder, f'{base_name}_Histogram_averaging.jpg')  
            output_path2 = os.path.join(output_folder, f'{base_name}_part_Histogram_averaging.jpg')  

            # 保存处理后的图片
            cv2.imwrite(output_path1, img1)  
            cv2.imwrite(output_path2, img2)  
            print(output_path1)
            print(output_path2)
        except Exception as e:  
            print(f"处理图片 {image_file} 时发生异常: {e}")  



#调节饱和度
def adjust_saturation(input_folder, output_folder,saturation_factor):  
    # 检查输出文件夹是否存在，如果不存在则创建  
    if not os.path.exists(output_folder):  
        os.makedirs(output_folder)  
  
    # 获取输入文件夹中的所有图片文件  
    image_files = [f for f in os.listdir(input_folder) if f.endswith('.jpg') or f.endswith('.png')]  
    
    # 对每个图片文件进行处理  
    for i, image_file in enumerate(image_files):  
        try:  
            # 打开图片文件  
            img_path = os.path.join(input_folder, image_file)  
            img = cv2.imread(img_path)
            
            if img is None:  
                print(f"无法读取文件 {image_file}")  
                continue  
            # 将图像从BGR转换到HSV颜色空间  
            hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)  
      
            # 分割HSV通道  
            h, s, v = cv2.split(hsv)  
    
            # 调整饱和度通道  
            s = s * saturation_factor  
            s = np.clip(s, 0, 255).astype(np.uint8) # 裁剪超出范围的饱和度值  
      
            # 合并调整后的通道  
            hsv_adjusted = cv2.merge((h, s, v))  
      
            # 将图像从HSV转换回BGR颜色空间  
            img1 = cv2.cvtColor(hsv_adjusted, cv2.COLOR_HSV2BGR)  
            # 创建输出文件路径，添加图片编号和后缀  
            base_name, _ = os.path.splitext(image_file)  
            output_path1 = os.path.join(output_folder, f'{base_name}_adjust_saturation_{saturation_factor}.jpg')  

            # 保存处理后的图片
            cv2.imwrite(output_path1, img1)  
            print(output_path1)
        except Exception as e:  
            print(f"处理图片 {image_file} 时发生异常: {e}") 
    
    
#调节色调
def tone(input_folder, output_folder):
    # 检查输出文件夹是否存在，如果不存在则创建  
    if not os.path.exists(output_folder):  
        os.makedirs(output_folder)  
  
    # 获取输入文件夹中的所有图片文件  
    image_files = [f for f in os.listdir(input_folder) if f.endswith('.jpg') or f.endswith('.png')]  
    
    # 对每个图片文件进行处理  
    for i, image_file in enumerate(image_files):  
        try:  
            # 打开图片文件  
            img_path = os.path.join(input_folder, image_file)  
            img = cv2.imread(img_path)
            
            if img is None:  
                print(f"无法读取文件 {image_file}")  
                continue  
            maxG = 128  # 修改颜色通道最大值，0<=maxG<=255
            lutHalf = np.array([int(i * maxG/255) for i in range(256)]).astype("uint8")
            lutEqual = np.array([i for i in range(256)]).astype("uint8")

            lut3HalfB = np.dstack((lutHalf, lutEqual, lutEqual))  # (1,256,3), B_half/BGR
            lut3HalfG = np.dstack((lutEqual, lutHalf, lutEqual))  # (1,256,3), G_half/BGR
            lut3HalfR = np.dstack((lutEqual, lutEqual, lutHalf))  # (1,256,3), R_half/BGR

            blendHalfB = cv2.LUT(img, lut3HalfB)  # B 通道衰减 50%
            blendHalfG = cv2.LUT(img, lut3HalfG)  # G 通道衰减 50%
            blendHalfR = cv2.LUT(img, lut3HalfR)  # R 通道衰减 50%
            # 创建输出文件路径，添加图片编号和后缀  
            base_name, _ = os.path.splitext(image_file)  
            output_path1 = os.path.join(output_folder, f'{base_name}_tone_blendHalfB.jpg')  
            output_path2 = os.path.join(output_folder, f'{base_name}_tone_blendHalfG.jpg')  
            output_path3 = os.path.join(output_folder, f'{base_name}_tone_blendHalfR.jpg')  
            # 保存处理后的图片
            cv2.imwrite(output_path1, blendHalfB)
            cv2.imwrite(output_path2, blendHalfG)
            cv2.imwrite(output_path3, blendHalfR)
            print(output_path1)
            print(output_path2)
            print(output_path3)
        except Exception as e:  
            print(f"处理图片 {image_file} 时发生异常: {e}")


#平均模糊
def Bluers(input_folder, output_folder):  
    # 检查输出文件夹是否存在，如果不存在则创建  
    if not os.path.exists(output_folder):  
        os.makedirs(output_folder)  
    # 获取输入文件夹中的所有图片文件  
    image_files = [f for f in os.listdir(input_folder) if f.endswith('.jpg') or f.endswith('.png')]  
    
    # 对每个图片文件进行处理  
    for i, image_file in enumerate(image_files):  
        try:  
            # 打开图片文件  
            img_path = os.path.join(input_folder, image_file)  
            img = cv2.imread(img_path)
            
            if img is None:  
                print(f"无法读取文件 {image_file}")  
                continue  
              
            MeanBlur3 = cv2.blur(img,(3,3))
            MeanBlur7 = cv2.blur(img,(7,7))
            
            # 创建输出文件路径，添加图片编号和后缀  
            base_name, _ = os.path.splitext(image_file)  
            output_path1 = os.path.join(output_folder, f'{base_name}_MeanBlur_3.jpg')  
            output_path2 = os.path.join(output_folder, f'{base_name}_MeanBlur_7.jpg')  

            # 保存处理后的图片
            cv2.imwrite(output_path1, MeanBlur3)
            cv2.imwrite(output_path2, MeanBlur7)
            print(output_path1)
            print(output_path2)
            
        except Exception as e:  
            print(f"处理图片 {image_file} 时发生异常: {e}") 
            
            
#高斯滤波
def  GaussBlur (input_folder, output_folder):
    if not os.path.exists(output_folder):  
        os.makedirs(output_folder)  
    # 获取输入文件夹中的所有图片文件  
    image_files = [f for f in os.listdir(input_folder) if f.endswith('.jpg') or f.endswith('.png')]  
    
    # 对每个图片文件进行处理  
    for i, image_file in enumerate(image_files):  
        try:  
            # 打开图片文件  
            img_path = os.path.join(input_folder, image_file)  
            image = cv2.imread(img_path)  
              
            if image is None:  
                print(f"无法读取文件 {image_file}")  
                continue  
            GaussBlur3 = cv2.GaussianBlur(image,(3,3),sigmaX=10,sigmaY=20)
            GaussBlur7 = cv2.GaussianBlur(image,(7,7),sigmaX=10,sigmaY=20)
            
           
            base_name, _ = os.path.splitext(image_file)  
            output_path1 = os.path.join(output_folder, f'{base_name}_GaussBlur_3.jpg')  
            output_path2 = os.path.join(output_folder, f'{base_name}_GaussBlur_7.jpg')  

            # 保存处理后的图片
            cv2.imwrite(output_path1, GaussBlur3)
            cv2.imwrite(output_path2, GaussBlur7)   
            print(output_path1)
            print(output_path2)

        except Exception as e:  
            print(f"处理图片 {image_file} 时发生异常: {e}")  


#指数滤波
def  Exponent(input_folder, output_folder):
    if not os.path.exists(output_folder):  
        os.makedirs(output_folder)  
  
    # 获取输入文件夹中的所有图片文件  
    image_files = [f for f in os.listdir(input_folder) if f.endswith('.jpg') or f.endswith('.png')]  
    
    # 对每个图片文件进行处理  
    for i, image_file in enumerate(image_files):  
        try:  
            # 打开图片文件  
            img_path = os.path.join(input_folder, image_file)  
            img = cv2.imread(img_path)  
              
            if img is None:  
                print(f"无法读取文件 {image_file}")  
                continue  
            a = 10.0
            noiseExponent = np.random.exponential(scale=a, size=img.shape)
            imgExponentNoise = img + noiseExponent
            imgExponentNoise = np.uint8(cv2.normalize(imgExponentNoise, None, 0, 255, cv2.NORM_MINMAX))
           
            base_name, _ = os.path.splitext(image_file)  
            output_path = os.path.join(output_folder, f'{base_name}_Exponen_.jpg')  
  
            # 保存处理后的图片
            cv2.imwrite(output_path, imgExponentNoise)     
            print(output_path)

        except Exception as e:  
            print(f"处理图片 {image_file} 时发生异常: {e}")  





#中值滤波
def median_filtering(input_folder, output_folder):
    if not os.path.exists(output_folder):  
        os.makedirs(output_folder)  
  
    # 获取输入文件夹中的所有图片文件  
    image_files = [f for f in os.listdir(input_folder) if f.endswith('.jpg') or f.endswith('.png')]  
    
    # 对每个图片文件进行处理  
    for i, image_file in enumerate(image_files):  
        try:  
            # 打开图片文件  
            img_path = os.path.join(input_folder, image_file)  
            img = cv2.imread(img_path)  
              
            if img is None:  
                print(f"无法读取文件 {image_file}")  
                continue  
            filtered_image  = cv2.medianBlur(img, 5)  
            base_name, _ = os.path.splitext(image_file)  
            output_path = os.path.join(output_folder, f'{base_name}blur.jpg')  
  
            # 保存处理后的图片
            cv2.imwrite(output_path, filtered_image)
            print(output_path)
            
        except Exception as e:  
            print(f"处理图片 {image_file} 时发生异常: {e}")

#对数滤波    
def Logarithmic_filtering(input_folder, output_folder):
    if not os.path.exists(output_folder):  
        os.makedirs(output_folder)  
  
    # 获取输入文件夹中的所有图片文件  
    image_files = [f for f in os.listdir(input_folder) if f.endswith('.jpg') or f.endswith('.png')]  
    
    # 对每个图片文件进行处理  
    for i, image_file in enumerate(image_files):  
        try:  
            # 打开图片文件  
            img_path = os.path.join(input_folder, image_file)  
            img = cv2.imread(img_path)  
              
            if img is None:  
                print(f"无法读取文件 {image_file}")  
                continue  
            image_float = img.astype(float)
            c = 1.0  # 这个常数可以根据需要调整  
            log_transformed = c * np.log(1.0 + image_float)  
            
            # 将变换后的图像数据缩放到合适的范围（例如，0-255）  
            log_transformed_scaled = cv2.normalize(log_transformed, None, 0, 255, cv2.NORM_MINMAX)  
            
            # 将数据类型转换回uint8  
            log_filtered_image = log_transformed_scaled.astype(np.uint8)  
            base_name, _ = os.path.splitext(image_file)  
            output_path = os.path.join(output_folder, f'{base_name}blur.jpg')  
  
            # 保存处理后的图片
            cv2.imwrite(output_path, log_filtered_image)
            
            
        except Exception as e:  
            print(f"处理图片 {image_file} 时发生异常: {e}")


#if __name__ == '__main__':
    

    # input_folder_1 = "neicha\\only_img"
    # output_folder_1 = "neicha\\resize"
    
    # image_files = [f for f in os.listdir(output_folder_1) if f.endswith('.jpg') or f.endswith('.png')]
    # for i, image_file in enumerate(image_files):
    #     os.remove(os.path.join(output_folder_1,image_file))
    #     print(image_file,'被清理')
    # resize_images(input_folder_1,output_folder_1)
    # output_folder_2="neicha\\translation"
    # image_files = [f for f in os.listdir(output_folder_2) if f.endswith('.jpg') or f.endswith('.png')]
    # for i, image_file in enumerate(image_files):
    #     os.remove(os.path.join(output_folder_2,image_file))
    #     print(image_file,'被清理')
    # translation_img(output_folder_1,output_folder_2)
    
    # output_folder_3="neicha\\images\\tarin"
    # image_files = [f for f in os.listdir(output_folder_3) if f.endswith('.jpg') or f.endswith('.png')]
    # for i, image_file in enumerate(image_files):
    #     os.remove(os.path.join(output_folder_3,image_file))
    #     print(image_file,'被清理')
    # #调节色调
    # tone(output_folder_2,output_folder_3)
    # #调节饱和度
    # adjust_saturation(output_folder_2,output_folder_3,1.5)
    # #调节对比度
    # Histogram_averaging(output_folder_2,output_folder_3,1)#0是灰度图 ，1是彩度图
    # #调节亮度
    # brightness(output_folder_2,output_folder_3)
    # #模糊滤波
    # Bluers(output_folder_2, output_folder_3)
    # #高斯滤波
    # GaussBlur (output_folder_2, output_folder_3)
    # #指数滤波
    # Exponent(output_folder_2, output_folder_3)
    # #中值滤波
    # median_filtering(output_folder_2, output_folder_3)
    # #对数滤波
    # Logarithmic_filtering(output_folder_2, output_folder_3)
    
    
    


    


