# Algoritmos TP 1

# Parte 1:
El objetivo de esta primera parte es poner en práctica el concepto de Estructuras de control de flujo de un
programa (secuencia, análisis de caso y repetición), como asimismo trabajar con tipos de datos simples y
estructurados (arrays), con expresiones lógicas, asignación interna y externa. También usaremos flujos
conocidos como “Archivos” y patrones algorítmicos de ordenamiento.
Vamos a desarrollar una aplicación para un sistema de delivery.
Para la organización de las entregas la empresa divide la ciudad en 6 zonas numeradas del 1 al 6.


# Ejercicio 1: Incorporación de repartidores
Ingreso de personas que formarán parte del staff de repartidores de la empresa
Se pide:
1) Generar el archivo “Repartidores.dat” con un registro por cada repartidor que se presentó para el
trabajo, estos datos se ingresan por teclado. Cada registro del archivo debe tener el dni, el nombre y
apellido y la zona de trabajo (del 1 al 6).
2) Informar cantidad de repartidores inscriptos para trabajar en cada una de las 6 zonas en que se
divide la ciudad.
3) Informar, si hubo, las zonas en las que no se postularon repartidores.
La finalización del ingreso de datos de los repartidores queda a criterio del grupo
Para realizar los puntos 2 y 3 utilizar estructuras de datos en memoria (arrays), no hacerlo con el archivo
generado.


# Ejercicio 2: Incorporación de negocios
Los rubros de los negocios a los que presta servicio la empresa de delivery son Heladería, Pizzería, Bebidas,
Parrilla.
Se ingresan los datos de los negocios que quieren trabajar con la empresa.
Por cada negocio se ingresa: Nombre de comercio, rubro y código de zona en la que se encuentra.
Se admite un máximo de 10 comercios por rubro por cada zona.
Al momento de ingresar los datos del comercio rechazar su incorporación si ya se completó el cupo para el
rubro en esa zona.
La finalización del ingreso de datos de los comercios queda a criterio del grupo.
Se pide:
1) Generar los archivos “Heladerias.dat”, “Pizzeria.dat”, “Bebidas.dat” y “Parrilla.dat” con los comercios
incorporados por cada rubro. Cada registro de cada uno de los archivos debe tener: nombre del
comercio y código de zona en la que se encuentra. Estos archivos deben estar ordenados
alfabéticamente por nombre del comercio.
2) Informar por cada zona si hay comercios para todos los rubros.
3) Informar, si hubo, rubros en los que no se hayan incorporado comercios.
Para realizar los puntos 2 y 3 utilizar estructuras de datos en memoria (arrays), no hacerlo con los archivos
generados.




# Parte 2:

El objetivo de esta segunda parte es poner en práctica el concepto de Estructuras dinámicas y la combinación de éstas con otras estructuras vistas en la primera parte.


# Ejercicio 1: Recepción de pedidos

Hacer un programa que presente al usuario un menú de opciones para:

1- Recibir un pedido
Se ingresan por teclado los datos de un pedido:
    -domicilio para hacer la entrega
    -zona de la entrega (1 a 6)
    -comercio en el que se hizo el pedido rubro del comercio
    -rubro del comercio
    -importe del pedido
Sólo se acepta el pedido si corresponde a un comercio de los inscriptos previamente y que zona de la entrega.
corresponda a la zona de entrega.
El pedido debe almacenarse en una estructura de datos donde se acceda a los mismos según el orden de llegada a la estructura. Es conveniente tener una estructura para cada una de las zonas.

2- Asignar pedidos a un repartidor
Dado el nombre de un repartidor y una cantidad de pedidos que entregará, eliminar esa cantidad de pedidos de la estructura donde estaban almacenados los pedidos en espera de esa zona y asignárselos al repartidor como pedidos entregados en una estructura de datos dinámica adecuada. El repartidor tiene que estar entre los inscriptos.

3- Mostrar
Mostrar todos los repartidores que hicieron entregas, ordenados por nombre, y por cada uno de ellos las entregas realizadas ordenadas de mayor a menor por importe.

4- Salir
Al finalizar el programa emitir el listado de comercios a los que se les ha realizado entregas, indicando el nombre del comercio y la cantidad entregas realizadas al mismo, ordenado alfabéticamente por nombre del comercio, utilizando un árbol binario de búsqueda. Se deberán cargar los datos en el mismo y recorrerlo INORDER para emitir el listado. 
El árbol binario se puede generar al finalizar el programa o ir almacenando los datos durante el proceso. La emisión del listado debe ser al finalizar el programa.