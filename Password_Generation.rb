
lower_chars = "abcdefghijklmnopqrstuvwxyz"
upper_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
number_chars = "0123456789"
special_chars = "!@#$%^&*()-=_+[]{};:'\"<>,.?/"

aFile = File.new("password.dic","w") #打开文件
for i in 1999...1999+100 #随机种子1999,1生成的密码100个
len = 16 #密码为16位
password =  Array.new(len)


srand(i) #随机种子是1999

n = len / 4 
for i in 0...n #循环4次
  password[i] = lower_chars[rand(n) % lower_chars.length] #0到3为小写
  password[i+n] = upper_chars[rand(n) % upper_chars.length] #4-7为大写
  password[i+2*n] = number_chars[rand(n) % number_chars.length] #8-11为数字
  password[i+3*n] = special_chars[rand(n) % special_chars.length] #12-15为特殊字符
end


j = len - 4 * n;
for i in 0...j
  password[i+4*n] = special_chars[rand(n) % special_chars.length] #多余的字符
end

#打乱顺序
for i in 0..32
  j = rand(n)  % len
  k = password[j]
  password[j] = password[i % len]
  password[i % len] = k
end


if aFile #写入到文件
  aFile.syswrite(password.join("") + "\n")

else
  puts "Unable to open file!"
end

end
