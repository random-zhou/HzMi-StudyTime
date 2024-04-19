import os
import shutil
def integration(input,output):
    # 确保目标文件夹存在，如果不存在则创建  
    os.makedirs(output, exist_ok=True)  
      
    # 遍历源文件夹中的所有文件  
    for filename in os.listdir(input):  
        src_file = os.path.join(input, filename)  
        dst_file = os.path.join(output, filename)  
        
        # 检查是否为文件（排除子文件夹）  
        #if os.path.isfile(src_file):  
        # 复制文件到目标文件夹  
        shutil.copy2(src_file, dst_file)
            