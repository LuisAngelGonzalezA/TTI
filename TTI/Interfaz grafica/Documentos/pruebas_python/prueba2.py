import MySQLdb

db = MySQLdb.connect(host="localhost", user="TT",passwd="TT", db="tornasol")
cursor = db.cursor()
cursor.execute("desc bateria")
print("--->",type(cursor))
print("\n\n")
lista=tuple()
for row in cursor:
    lista=list(lista)
    lista.append(row[0])
    lista=tuple(lista)
    #lista.extend(row[0])
    #print(row[0])
print(lista)
lista=list(lista)
print(lista[1])

del lista[0]
del lista[0]
lista=tuple(lista)
print(lista)

cursor.execute("select*from bateria")
lista=list()
for row in cursor:
    print("--->",type(row))
    print(row)
    lista=list(row)

    del lista[0]
    del lista[0]
    lista=tuple(lista)
    print("--->",type(lista))
    print(lista)



