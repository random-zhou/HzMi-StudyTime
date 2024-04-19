import os
import shutil



def compound(input_dir,output_path):
    subdirs = [os.path.join(input_dir, name) for name in os.listdir(input_dir) if os.path.isdir(os.path.join(input_dir, name))]  
    
    for subdir in subdirs:
        #image_files = [f for f in os.listdir(subdir) if f.endswith('.jpg')]  
        image_files = [f for f in os.listdir(subdir) if f.endswith('.txt')]  
        for img_file in image_files:
                src_file = os.path.join(subdir, img_file)  
                dst_file = os.path.join(output_path, img_file)  
                # 检查是否为文件（排除子文件夹）  
                if os.path.isfile(src_file):  
                    # 复制文件到目标文件夹  
                    print(src_file)
                    shutil.copy2(src_file, dst_file)
        





if __name__ == '__main__':
    compound('initial_image\\label_train_seed','initial_image\\image_test\\txt')
