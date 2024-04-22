import os
import uuid
import cv2

def Disorderly(img_path,label_path):
    """  
    将指定目录下的图片文件和对应标签文件进行重命名，文件名被替换为随机的UUID。  
      
    参数:  
    img_path (str): 图片文件所在的目录路径。  
    label_path (str): 标签文件所在的目录路径。  
      
    注意：  
    - 该函数假设图片文件和标签文件具有相同的文件名前缀（不包含扩展名）。  
    - 如果图片或标签文件不存在，或者重命名过程中发生异常，会打印错误信息。  
    建议先alignment()对齐
    """  
    # 获取img_path目录下所有jpg或png扩展名的图片文件列表  
    image_files = [f for f in os.listdir(img_path) if f.endswith('.jpg') or f.endswith('.png')]    
  
    # 遍历图片文件列表  
    for filename in image_files[:]:  
        try:     
            # 获取文件名（不包含扩展名），用于后续生成新的文件名和标签文件名  
            base_name, _ = os.path.splitext(filename)  
  
            # 生成一个随机的UUID  
            file_name_new = str(uuid.uuid4())  
  
            # 构造新的图片文件名（UUID + .jpg）  
            img_file_new = file_name_new + '.jpg'  
  
            # 对图片文件进行重命名，使用新生成的文件名  
            os.rename(os.path.join(img_path, filename), os.path.join(img_path, img_file_new))   
  
            # 打印重命名前后的文件名  
            print(filename, 'to', img_file_new)  
  
            # 构造对应的标签文件名（基于原始文件名，仅扩展名不同）  
            label_name = base_name + '.txt'  
  
            # 构造新的标签文件名（UUID + .txt）  
            label_name_new = file_name_new + '.txt'  
  
            # 对标签文件进行重命名，使用新生成的文件名  
            os.rename(os.path.join(label_path, label_name), os.path.join(label_path, label_name_new))   
  
            # 打印标签文件重命名前后的文件名  
            print(label_name, 'to', label_name_new)  
  
        # 如果在重命名过程中发生异常，捕获异常并打印错误信息  
        except Exception as e:    
            print(f"处理图片 {filename} 时发生异常: {e}")  

    
    
    













