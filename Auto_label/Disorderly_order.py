import os
import uuid
import cv2

def Disorderly(img_path,label_path):
    image_files = [f for f in os.listdir(img_path) if f.endswith('.jpg') or f.endswith('.png')]  
    for filename in image_files[:]:
        try:   
            base_name, _ = os.path.splitext(filename)#用于获取label的名字
            file_name_new = str(uuid.uuid4())
            img_file_new=file_name_new+'.jpg'
            os.rename(os.path.join(img_path,filename), os.path.join(img_path,img_file_new)) 
            print(filename,'to',img_file_new)
            label_name=base_name+'.txt'
            label_name_new=file_name_new+'.txt'
            os.rename(os.path.join(label_path,label_name), os.path.join(label_path,label_name_new)) 
            print(label_name,'to',label_name_new)
        except Exception as e:  
            print(f"处理图片 {filename} 时发生异常: {e}") 

    
    
    
if __name__ == "__main__":
    img_path='data\\1712389104\\images\\val'
    label_path='data\\1712389104\\labels\\val'
    Disorderly(img_path,label_path)














