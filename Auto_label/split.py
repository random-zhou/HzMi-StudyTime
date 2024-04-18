import os
import shutil

def split(split_num,input_path,output_dir):
    os.makedirs(output_dir, exist_ok=True)
    for i in range(split_num):
        output_dir_seed=os.path.join(output_dir,str(i))
        os.makedirs(output_dir_seed, exist_ok=True)
        #files = [f for f in os.listdir(output_dir_seed) if f.endswith('.jpg') or f.endswith('.png')]
        files = [f for f in os.listdir(output_dir_seed) if f.endswith('.txt')]

        for i, image_file in enumerate(files):
            os.remove(os.path.join(output_dir_seed,image_file))
            print(image_file,'被清理')
    #image_files = [f for f in os.listdir(input_path) if f.endswith('.jpg') or f.endswith('.png')]  
    image_files = [f for f in os.listdir(input_path) if f.endswith('.txt')]  

    mean=int(len(image_files)/split_num)+1
    count=0
    count_file=0
    for img_file in image_files:
        output_dir_seed=os.path.join(output_dir,str(count))
        src_file = os.path.join(input_path, img_file)  
        dst_file = os.path.join(output_dir_seed, img_file)  
        # 检查是否为文件（排除子文件夹）  
        if os.path.isfile(src_file):  
            # 复制文件到目标文件夹  
            print(src_file)
            shutil.copy2(src_file, dst_file)
            count_file+=1
            if count_file>=mean:
                count+=1
                count_file=0



if __name__ == '__main__':
    split(5,'initial_image\\labels\\train','initial_image\\label_train_seed')









