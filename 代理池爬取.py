import requests
from  lxml import etree
#https://www.89ip.cn/index_2.html
#//table[@class="layui-table"]//tr[position()>1]//td[1]/text()
#//table[@class="layui-table"]//tr[position()>1]//td[2]/text()

url ='http://www.66ip.cn/{}.html'
def get_url(url):
    html = requests.get(url).text
    html = etree.HTML(html)
    ipResult = html.xpath('//table[@bordercolor="#6699ff"]//tr[position()>1]//td[1]/text()')
    #print(ipResult)
    portResult = html.xpath('//table[@bordercolor="#6699ff"]//tr[position()>1]//td[2]/text()')
    #print(portResult)
    if (len(ipResult) == len(portResult)):
        for a,b in zip(ipResult,portResult):
            PORT = b.strip()
            IP = a.strip()
            DL =(IP +':'+PORT)
            check(DL)
    else:
        print("长度不对称!")
        

 #result2 = html.xpath('//td/a[@target="_blank"]/text()')
 #print(result)
 #print(result2)

def check(DL):
    url ='http://%s'% DL.rstrip()
    try:
        result = requests.get(url,timeout=5)
        print(DL +"######代理可用")
        with open ('DL.txt','a')as f:
             f.write(DL +"\n")
    except:
        print(DL +'代理不可用')

for i in range(200,300+1):
    print('http://www.66ip.cn/{}.html'.format(i))
    get_url('http://www.66ip.cn/{}.html'.format(i))

 
