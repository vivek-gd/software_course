import pymysql

conn = pymysql.connect(host='localhost', user='root', password='123456', database='sys', charset='utf8')
cursor = conn.cursor()
sql ='select version()'
cursor.execute(sql)
retdat = cursor.fetchall()
for row in retdat:
    print(row[0])
cursor.close()
conn.close()