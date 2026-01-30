import mysql.connector

mydb=mysql.connector.connect(
    host="localhost",
    user="root",
    password="123456",
    database="dbabc"
)

mycursor=mydb.cursor()
mycursor.execute("select * from table")
result=mycursor.fetchall()

for row in result:
    print(row)