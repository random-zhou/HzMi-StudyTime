import os

# 定义函数，用于更改图片和对应标签文件的名称，加入标志位
def Change_name(class_name, img_path, label_path):  
    # 获取指定图片路径下所有以.jpg或.png结尾的文件列表  
    image_files = [f for f in os.listdir(img_path) if f.endswith('.jpg') or f.endswith('.png')]  
  
    # 遍历图片文件列表  
    for filename in image_files[:]:  # 使用[:]创建列表的一个副本，避免在迭代中修改原列表  
        try:  
            # 分离文件名和扩展名，得到基本名称（不包含扩展名）  
            base_name, _ = os.path.splitext(filename)  
  
            # 构造新的文件名，即在原基本名称前添加新的类名  
            file_name_new = str(class_name) + base_name  
  
            # 如果原文件是.jpg，则新文件名也添加.jpg扩展名  
            img_file_new = file_name_new + '.jpg'  
  
            # 重命名图片文件，将原文件移动到新文件名  
            os.rename(os.path.join(img_path, filename), os.path.join(img_path, img_file_new))  
  
            # 打印出原文件名和新文件名  
            print(filename, 'to', img_file_new)  
  
            # 构造原标签文件名，假设标签文件名与图片文件名（不含扩展名）相同，扩展名为.txt  
            label_name = base_name + '.txt'  
  
            # 构造新标签文件名  
            label_name_new = file_name_new + '.txt'  
  
            # 重命名标签文件，将原文件移动到新文件名  
            os.rename(os.path.join(label_path, label_name), os.path.join(label_path, label_name_new))  
  
            # 打印出原标签文件名和新标签文件名  
            print(label_name, 'to', label_name_new)  
  
        # 如果在重命名过程中发生异常，捕获异常并打印错误信息  
        except Exception as e:  
            print(f"处理图片 {filename} 时发生异常: {e}")  
            
            