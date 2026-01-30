import pymysql

conn = pymysql.connect(host='127.0.0.1', user='newuser', password='123456', database='dbsclab2025', charset='utf8')
cursor = conn.cursor()
sql="select name,salary from instructor;"
cursor.execute(sql)
retdat=cursor.fetchall()
for row in retdat:
    print(row[0],",",row[1])


cursor.close()
conn.close()