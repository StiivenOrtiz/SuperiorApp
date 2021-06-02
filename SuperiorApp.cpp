#include <iostream> //Libreria para entradas y salidas
#include <wchar.h> // Poder colocar caracteres especiales
#include <stdlib.h> // Gestión de memoria dinámica, control de procesos y otras cosas
#include <string.h> // Librería de manipulación de vectores de char / manipulación de strings

using namespace std;

/*	Se declaran las variables constantes de: La ruta de archivo de los usuarios y productos,
		al igual que el tamaño que van a tener variables como nombres y apellidos y telefonos. */

const char RutaArchivoUsuarios[] = "usuarios.bin";
const char RutaArchivoProductos[] = "productos.bin";
const int Tam_NombresApellidos = 15;
const int Tam_CorreoContrasena = 40;
const int Tam_Telefono = 15;

//	Ahora se declaran las estructuras que van a ser utilizadas en el código, "usuarios, productos, carrito".

struct sUsuario
{
  char Nombre[Tam_NombresApellidos];
  char Apellido[Tam_NombresApellidos];
  char Correo[Tam_CorreoContrasena];
  char Contrasenia[Tam_CorreoContrasena];
  long Saldo;
  char Direccion[100];
  char Genero;
  char FechaNacimiento[10];
} Usuarios[10000]; // Se crea una reserva de 10000 usuarios.

struct sProductos
{
  char Articulo[Tam_NombresApellidos];
  char Categoria[Tam_NombresApellidos];
  char Unidad[Tam_NombresApellidos];
  long Precio;
} ListaDeProductos[20]; // También se crea un arreglo de esta estructura de 20, para dejar una reserva.

struct sCarrito
{
  sProductos Producto; // Se añade la estructura de producto, para ser más fácil su manipulación.
  int Cantidad;
} Carrito_Compras[50]; // Al igual que en la anterior estructura se crea un arreglo de 50, para tener una reseva en caso de ser más.

/*  Vamos a declarar las variables necesarias para ser utilizadas luego en funciones y asi mismo en el programa, en este caso son los contadores de productos, carrito
    y usuarios. Tambien hacemos la creación de una variable para saber que usuario ingresará.*/

int Cantidad_Usuarios = 0;
int Cantidad_Productos = 0;
int Cantidad_PCarrito = 0;
int Indice_Usuario = -1;
long Valor_total=0;

// Ahora se declaran las funciones que van a ser utilizadas en el programa.

int Cargar_Usuarios(sUsuario Usuarios[]);
int Cargar_Productos(sProductos ListaDeProductos[]);
void Guardar_Usuarios(sUsuario Usuarios[], int Cantidad_Usuarios);
void Menu_Inicial(sUsuario Usuarios[]);
bool Iniciar_Sesion(sUsuario Usuarios[]);
int Registrarse(sUsuario Usuarios[], int cant_usuarios);
void Menu_SesionIniciada(sUsuario Usuarios[]);
void Agregar_Al_Carrito(sProductos ListaDeProductos[], sCarrito Carrito_Compras[]);
int Listar_Categoria(sProductos ListaDeProductos[], sProductos ListaCategoriaP[], sCarrito Carrito_Compras[], sCarrito ListaCategoriaC[], char Categoria[], int Contador, int CarritoOProductos);
int LlenarCarrito(sProductos ListaCategoriaP[], int Contador, sCarrito Carrito_Compras[]);
void ModificarCarrito();
int EliminarArticulo(sCarrito Carrito_Compras[]);
long Mostrar_Carrito(sCarrito Carrito_Compras[]);
void Consultar_Saldo(sUsuario Usuarios[]);
void Comprar_Puntos(sUsuario Usuarios[]);
int Pagar_Carrito(sUsuario Usuarios[], sCarrito Carrito_Compras[]);

int main()
{
    setlocale(LC_ALL, ""); // Se hace uso de la función setlocale, para poder usar tildes y carácteres especiales.

    Cantidad_Productos = Cargar_Productos(ListaDeProductos);

    if(Cantidad_Productos==-2){
        return 0;
    }

    Cantidad_Usuarios = Cargar_Usuarios(Usuarios);

  	// Este menu sera desplegado para llamar las demas funciones, siendo este la raiz de todo las demas.

    int opcion; // Declaración de la opción de este menú.

  do
  {
    cout<<"Bienvenido a SuperiorApp"<<endl;
    cout<<"1. Iniciar Sesión"<<endl;
    cout<<"2. Registrarse"<<endl;
    cout<<"3. Salir"<<endl;
    cout<<"Digite su opción: ";
    cin>>opcion;
    cout<<endl;

    switch(opcion)
    {
    case 1:

      if(Iniciar_Sesion(Usuarios) == true)
      {
        Menu_SesionIniciada(Usuarios);
      }
      break;

      case 2:

        Cantidad_Usuarios = Registrarse(Usuarios, Cantidad_Usuarios);
        Guardar_Usuarios(Usuarios, Cantidad_Usuarios);

        break;

      case 3:

        cout<<"Gracias, vuelva pronto."<<endl;
        Guardar_Usuarios(Usuarios, Cantidad_Usuarios);
        cout<<endl;
        break;

      default:

        cout<<"Error, vuelva a digitar una opción"<<endl;
        cout<<endl;
        break;

      }

  }
  while(opcion!=3);

  return 0;
}

bool Iniciar_Sesion(sUsuario Usuarios[])
{
  // Creación de las variables que se van a utilizar para comparar.
  char Correo[Tam_CorreoContrasena];
  char Contrasenia[Tam_CorreoContrasena];

  // Creación de booleano bandera para dar aviso al error
  bool bandera=false;

  // Perdir que le de valor a estas variables para luego compararles.
  cout<<"Ingrese su Correo: ";
  cin>>Correo;
  cout<<"Ingrese su Contraseña: ";
  cin>>Contrasenia;
  cout<<endl;

  // Iniciamos una busqueda del correo con la cantidad de usuarios.
  for (int i = 0; i < Cantidad_Usuarios; i++)
  {
    // Por medio de la función de de strcmp podemos verificar si el valor ingresado es existente en el arreglo de estructuras de los usuarios.
    if (strcmp(Usuarios[i].Correo, Correo) == 0)
    {
      bandera=true;
      // Ahora validamos si la contraseña tambien se encuentra.
      if (strcmp(Usuarios[i].Contrasenia, Contrasenia) == 0)
      {
        // En caso de que se encuentre, entonces retornará true
        cout<<"Ha iniciado sesión correctamente."<<endl;
        system("pause");
        system("cls");
        Indice_Usuario = i;
        return true;
      }
    }
  }
  // Aviso al error mediante un if:
  if(bandera==true){
  cout<<"La contraseña es incorrecta.."<<endl;
  cout<<endl;
  }else if(bandera==false){
  cout<<"El correo no ha sido encontrado."<<endl;
  cout<<endl;
  }

  return false;
}

int Registrarse(sUsuario Usuarios[], int cant_usuarios)
{
  // Creamos un nuevo usuario en base a la estructura de un usuario, para recibir la información.
  sUsuario NuevoUsuario;
  // Creamos un booleano para verificar si el correo exite en el arreglo de estructuras de usuarios.
  bool Bandera;

  cout<<endl;
  // Empezamos a pedir los datos de los usuarios.
  cout<<"Ingrese su nombre: ";
  cin>>NuevoUsuario.Nombre;
  cout<<"Ingrese su apellido: ";
  cin>>NuevoUsuario.Apellido;
  cout<<endl;
  cout<<"A continuación ingrese el correo que desea utilizar. (Si el correo es existente, por favor ingrese otro)"<<endl; // Le damos aviso previo al usuario, para que tenga cuidado con el correo a colocar.
  cout<<endl;

  do
  {
    Bandera=false; // Le damos el valor de falso, en caso de que salga así entonces será un correo que no está. Tambien sirve para verificacion del genero.
    cout<<"Ingrese su correo: ";
    cin>>NuevoUsuario.Correo;
    for(int i=0; i<cant_usuarios; i++)
    {
      // verificamos si el correo es existente.
      if (strcmp(Usuarios[i].Correo, NuevoUsuario.Correo) == 0)
      {
        // Si este está, entonces la bandera tomará el valor de verdadero.
        Bandera=true;
        cout<<"El correo ya es existente, por favor ingrese otro."<<endl; // Le avisamos al usuario que el correo es existente.
      }
    }
  }
  while(Bandera==true);  // Si Bandera es verdadera, entonces el correo existe, por lo tanto se va a volver a repetir el ciclo.

  // Seguimos pidiendo datos a los usuarios
  cout<<"Ingrese su contraseña: ";
  cin>>NuevoUsuario.Contrasenia;
  NuevoUsuario.Saldo=0; // El saldo será definido automaticamente en 0, para luego hacer uso de la función correctamente.
  cout<<"Ingrese su dirección: ";
  cin>>NuevoUsuario.Direccion;
  do
  {
    Bandera=false;
    cout<<"Ingrese su genero (F) o (M): ";
    cin>>NuevoUsuario.Genero;
    if(NuevoUsuario.Genero=='M'||NuevoUsuario.Genero=='F')
    {
      Bandera=true;
    }
  }
  while(Bandera!=true);  // Si el genero ingresado por el usuario es igual a M o F, entonces seguirá, de lo contrario volverá a pedirlo.

  cout<<"Ingrese su fecha de nacimiento (DD/MM/AAAA): ";
  cin>>NuevoUsuario.FechaNacimiento;

  Usuarios[cant_usuarios] = NuevoUsuario; // Utilizamos el nuevo usuario para darle agregarlo al arreglo de estructuras.

  cout<<endl;
  cout<<"-Registro exitoso-"<<endl;
  system("pause");
  system("cls");

  return cant_usuarios+1; // aumentamos uno más para que el arreglo de estructuras aumente.
}

void Menu_SesionIniciada(sUsuario Usuarios[])
{
  int opcion;
  // Mensaje del nombre completo del usuario
  cout<<"¡Bienvenido a SuperiorApp "<<Usuarios[Indice_Usuario].Nombre<<" "<<Usuarios[Indice_Usuario].Apellido<<"!"<<endl;
  // Este es el menú cuando inician sesión
  do
  {
    cout<<"\nPor favor seleccione una opción "<<endl;

    cout<<"\n1. Agregar al carrito de mercado"<<endl;
    cout<<"2. Modificar carrito de mercado "<<endl;
    cout<<"3. Ver carrito de mercado "<<endl;
    cout<<"4. Pagar carrito de mercado "<<endl;
    cout<<"5. Comprar puntos "<<endl;
    cout<<"6. Consultar saldo "<<endl;
    cout<<"7. Salir"<<endl;
    cout<<"Digite su opción: "; cin>>opcion;

    switch(opcion)
    {
      case 1:

        system("cls");
        Agregar_Al_Carrito(ListaDeProductos, Carrito_Compras);

        break;

      case 2:

        system("cls");
        ModificarCarrito();

        break;

      case 3:

        system("cls");
        Valor_total=Mostrar_Carrito(Carrito_Compras);

        break;

      case 4:

        system("cls");
        Valor_total=Pagar_Carrito(Usuarios, Carrito_Compras);

        break;

      case 5:

        system("cls");
        Comprar_Puntos(Usuarios);

        break;

      case 6:

        system("cls");
        Consultar_Saldo(Usuarios);

        break;

      case 7:

        system("cls");
        cout<<"Saliendo de la cuenta..."<<endl;
        Cantidad_PCarrito=0;
        cout<<endl;

        break;

      default:

        system("cls");
        cout<<"Error, vuelva a digitar una opción."<<endl;
        cout<<endl;

        break;
    }
  }
  while(opcion != 7);
}

// Función para agregar productos al carrito
void Agregar_Al_Carrito(sProductos ListaDeProductos[], sCarrito Carrito_Compras[]){
  sProductos ListadoCategoria[50]; // Creación de la estructura donde se va a guardar el listado.
  int CantidadListado=0; // Cantidad del listado para mostrar el listado.
  sCarrito Aux[2]; // Para que funcione la función creada, se necesitará de la creación de este arreglo de estructuras.
  // Esta función tiene la interfaz de un menú.
  int opcion;
  // Con ayuda de un switch, se tomara la categoria.
  char lacteos[]="Lacteos", frutas[]="Frutas", verduras[]="Verduras", bebidas[]="Bebidas";

  // Desplega un menú para que el usuario seleccione la categoria de la que desea tomar el producto.
  do{
    cout<<"----Categorias----"<<endl;
    cout<<"1. Lácteos"<<endl;
    cout<<"2. Frutas"<<endl;
    cout<<"3. Verduras"<<endl;
    cout<<"4. Bebidas"<<endl;
    cout<<"5. Volver"<<endl;
    cout<<"Seleccione la categoria de la que quiere agregar su producto: "; cin>>opcion;
    cout<<endl;

    switch (opcion){

    case 1:

      system("cls");
      // Genera un listado de la categoria
      CantidadListado = Listar_Categoria(ListaDeProductos, ListadoCategoria, Carrito_Compras, Aux, lacteos, CantidadListado, 0);
      // Manda el listado a la función de llenar carrito.
      Cantidad_PCarrito = LlenarCarrito(ListadoCategoria, CantidadListado, Carrito_Compras);

      break;

    case 2:

      system("cls");
      CantidadListado = Listar_Categoria(ListaDeProductos, ListadoCategoria, Carrito_Compras, Aux, frutas, CantidadListado, 0);
      Cantidad_PCarrito = LlenarCarrito(ListadoCategoria, CantidadListado, Carrito_Compras);

      break;

    case 3:

      system("cls");
      CantidadListado = Listar_Categoria(ListaDeProductos, ListadoCategoria, Carrito_Compras, Aux, verduras, CantidadListado, 0);
      Cantidad_PCarrito = LlenarCarrito(ListadoCategoria, CantidadListado, Carrito_Compras);

      break;

    case 4:

      system("cls");
      CantidadListado = Listar_Categoria(ListaDeProductos, ListadoCategoria, Carrito_Compras, Aux, bebidas, CantidadListado, 0);
      Cantidad_PCarrito = LlenarCarrito(ListadoCategoria, CantidadListado, Carrito_Compras);

      break;

    case 5:

      system("cls");
      cout<<"Volviendo..."<<endl;

      break;

    default:

      system("cls");
      cout<<"\nError al seleccionar la categoria, por favor ingrese su opción nuevamente"<<endl; // Aviso si el usuario ingresa una opción no válida.
      cout<<endl;

      break;
    }
  }while(opcion!=5);
}

// Función para listar por categoria.
int Listar_Categoria(sProductos ListaDeProductos[], sProductos ListaCategoriaP[], sCarrito Carrito_Compras[], sCarrito ListaCategoriaC[], char Categoria[], int Contador, int CarritoOProductos){

  Contador=0; // Le damos el valor de cero para que no vuelva a contar desde el número anterior, si es que hubo un listado antes.

  // Según la opción será un listado de carrito o de productos. 0 para productos, 1 para carrito de compras.
  if(CarritoOProductos==0){
    for(int i=0; i<Cantidad_Productos; i++){
      if (strcmp(ListaDeProductos[i].Categoria, Categoria) == 0){ // Verificamos que la categoria sea la misma.
        ListaCategoriaP[Contador]=ListaDeProductos[i]; // Si es la misma, entonces la lista va a tomar el valor del producto que tenga la misma categoria.
        Contador++; // aumentamos el contador, para que el listado siga avanzando.
      }
    }
  }else if(CarritoOProductos==1){
    for(int i=0; i<Cantidad_PCarrito; i++){
      if (strcmp(Carrito_Compras[i].Producto.Categoria, Categoria) == 0){
        ListaCategoriaC[Contador]=Carrito_Compras[i];
        Contador++;
      }
    }
  }

  //Imprimimos la lista creada.
  cout<<"---Productos de la categoria "<<Categoria<<"---"<<endl;

  if(CarritoOProductos==0){
    for(int i=0; i<Contador; i++){
      cout<<i<<" - "<<ListaCategoriaP[i].Articulo<<" - "<<ListaCategoriaP[i].Categoria<<" - "<<ListaCategoriaP[i].Unidad<<" - $"<<ListaCategoriaP[i].Precio<<endl;
    }
  }else if(CarritoOProductos==1){
    for(int i=0; i<Contador; i++){
      cout<<i<<" - "<<ListaCategoriaC[i].Producto.Articulo<<" - "<<ListaCategoriaC[i].Producto.Categoria<<" - "<<ListaCategoriaC[i].Producto.Unidad<<" x"<<ListaCategoriaC[i].Cantidad<<" - $"<<ListaCategoriaC[i].Producto.Precio<<endl;
      cout<<endl;
    }
  }
  return Contador; // Devolvemos el contador, para que sea utilizado en otras funciones.
}

// Función para agregar al carrito de mercado.
int LlenarCarrito(sProductos ListaCategoriaP[], int Contador, sCarrito Carrito_Compras[]){
  sCarrito ProductoAgregar; // Genera una estructura de carrito para agregar el nuevo producto al carrito.
  int IndiceProducto, CantidadDelProducto; // Declaración de variables importantes a la hora de agregar al carrito.
  // Pedimos los datos al usuario.
  do{
    cout<<"\nPor favor ingrese el número del producto: "; cin>>IndiceProducto;
  }while(IndiceProducto>Contador-1);
  
  cout<<"Ingrese la cantidad del producto: "; cin>>CantidadDelProducto;

  // Llenamos la estructura creada, por medio de el listado, y los datos pedidos.
  ProductoAgregar.Producto = ListaCategoriaP[IndiceProducto];
  ProductoAgregar.Producto.Precio = ProductoAgregar.Producto.Precio*CantidadDelProducto; // El precio se multiplica por la cantidad del producto deseado.
  ProductoAgregar.Cantidad = CantidadDelProducto;

  Carrito_Compras[Cantidad_PCarrito] = ProductoAgregar;
    
  system("cls");
  
  cout<<"\n¡Producto agregado al carrito de compras con éxito!"<<endl; // Se le da aviso al usuario de que su producto ha sido agregado.
  cout<<endl;

  return Cantidad_PCarrito+1; // retornamos que el carrito de compras aumenta.
}

// Función para modificar el carrito de mercado.
void ModificarCarrito(){
  int opcion;
  do
  {
    cout<<"-Modificar Carrito de Compras-"<<endl;
    cout<<"1. Eliminar articulo"<<endl;
    cout<<"2. Volver"<<endl;
    cout<<"Ingrese su opción: "; cin>>opcion;

    switch (opcion)
    {
    case 1:

      system("cls");
      Cantidad_PCarrito=EliminarArticulo(Carrito_Compras); // Llamamos a la función para eliminar el articulo.
      Valor_total=Mostrar_Carrito(Carrito_Compras); // Llamamos a la función de mostrar carrito, para mostrar como quedó despues de eliminar el articulo.

      break;

    case 2:

      system("cls");
      cout<<"Volviendo..."<<endl;

      break;

    default:

      system("cls");
      cout<<"\n Error, por favor ingrese una opción válida"<<endl;
      cout<<endl;

      break;
    }

  } while(opcion!=2);

}

// Función para eliminar los productos del carrito de mercado.
int EliminarArticulo(sCarrito Carrito_Compras[]){
  Valor_total=Mostrar_Carrito(Carrito_Compras); // Llamamos la función para que observe su carrito de compras y decida que articulo eliminar, de una vez se aprovecha para guardar el valor total.
  int indice; // Declaración de variable que guardará el indice del articulo que el usuario desea eliminar.
  cout<<"\nIngrese el indice del articulo que desea eliminar: "; cin>>indice; // Pedimos el indice al usuario.
  if(indice >= 0 && indice < Cantidad_PCarrito){ // Verificamos que el indice no sea menor de 0 y sea menor que la cantidad de articulos en el carrito.
    for (int i = indice; i < Cantidad_PCarrito - 1; i++) {
      Carrito_Compras[i] = Carrito_Compras[i + 1]; // Eliminamos el articulo, moviendo el vector hacia la izquierda, cubriendo el articulo seleccionado.
    }
    cout << endl << "Articulo eliminado exitosamente" << endl; // Le avisamos al usuario que exitosamente ha sido eliminado el articulo.
    return Cantidad_PCarrito - 1;
  }else{
    cout<<"ERROR: El articulo "<<indice<<" no existe."<<endl; // Le decimos que hubo un error al colocar el indice del articulo.
    return Cantidad_PCarrito; // Devolvemos la misma cantidad de articulos en el carrito de mercado.
  }
}

// Función para mostrar los productos del carrito de mercado
long Mostrar_Carrito(sCarrito Carrito_Compras[])
{
  long Total=0; // Acumulador del total
  if(Cantidad_PCarrito>0){
    cout<<"A continuación se le van a mostrar los productos que tiene en su carrito"<<endl;
    cout<<endl;
    //Se le muesta los productos
    for(int i = 0; i < Cantidad_PCarrito; i++)
    {
      cout<<i<<" - "<<Carrito_Compras[i].Producto.Articulo<<" - "<<Carrito_Compras[i].Producto.Categoria<<" - "<<Carrito_Compras[i].Producto.Unidad<<" x"<<Carrito_Compras[i].Cantidad<<" - $"<<Carrito_Compras[i].Producto.Precio<<endl;
      Total+=Carrito_Compras[i].Producto.Precio;
      cout<<endl;
    }
    cout<<"Precio Total: $"<<Total<<endl;
    return Total;
  }

  cout<<"No hay articulos en el carrito de compras."<<endl;
  cout<<"Volviendo al menú..."<<endl;
  return 0;
}

// Función para consultar saldo
void Consultar_Saldo(sUsuario Usuarios[])
{
  cout<<"Consultando saldo..."<<endl;
  cout<<"\nSu saldo actual es: "<<Usuarios[Indice_Usuario].Saldo<<" puntos"<<endl; // Muestra el saldo actual
}

// Función para comprar puntos
void Comprar_Puntos(sUsuario Usuarios[])
{
  long Puntos_Comprados;

  cout<<"Sus puntos actuales son: "<<Usuarios[Indice_Usuario].Saldo<<endl; // Muestra los puntos actuales

  cout<<"\nPor favor digite los puntos que quiera comprar: ";
  cin>>Puntos_Comprados;

  cout<<"\nRealizando transacción..."<<endl;

  Usuarios[Indice_Usuario].Saldo += Puntos_Comprados; // Sumatoria total de puntos
  Guardar_Usuarios(Usuarios, Cantidad_Usuarios);

  cout<<"\n¡Transacción realizada exitosamente!"<<endl;

  cout<<"\nSu nuevo saldo es de: "<<Usuarios[Indice_Usuario].Saldo;
  cout<<endl;
}

//Función pargar carrito de mercado
int Pagar_Carrito(sUsuario Usuarios[], sCarrito Carrito_Compras[])
{
  int opcion, opcion_puntos, incentivo=0;
  long CalculoNuevoSaldo = 0; //variable para saber si puede pagar el valor total

  if(Cantidad_PCarrito>0){
    do{
     Valor_total=Mostrar_Carrito(Carrito_Compras); //llamado de la función que muestra los productos del carrito de mercado y obtener el valor total del carrito.

     cout<<"\nSu saldo actual es: "<<Usuarios[Indice_Usuario].Saldo<<" puntos"<<endl; // Muestra el saldo actual

     cout<<"\n¿Desea realizar el pago?: "<<endl; //autorización al cliente para realizar el pago
     cout<<"1. Si"<<endl;
     cout<<"2. No"<<endl;
     cout<<"\nDigite su opcion: ";cin>>opcion;

     system("cls");

     switch(opcion){
        case 1:

          if(Usuarios[Indice_Usuario].Saldo>=Valor_total){
          incentivo=Valor_total*.01;
            cout<<"Realizando transacción..."<<endl;
            CalculoNuevoSaldo=Usuarios[Indice_Usuario].Saldo-Valor_total;
            Usuarios[Indice_Usuario].Saldo=CalculoNuevoSaldo;
            Usuarios[Indice_Usuario].Saldo+=incentivo;
            Cantidad_PCarrito=0;
            cout<<"\n¡Transacción realizada con éxito!"<<endl;
            cout<<"\nSu nuevo saldo es de: "<<Usuarios[Indice_Usuario].Saldo<<endl;
            cout<<"\nDentro de unos minutos su pedido será enviado a la dirección"<<endl;
            cout<<"-"<<Usuarios[Indice_Usuario].Direccion<<"-"<<endl;
            cout<<"\n¡Gracias por utilizar SuperiorApp!"<<endl;
            cout<<"A continuación será enviado al menú..."<<endl;
            return 0;
          }else{
            cout<<"Usted no posee saldo suficiente para realizar esta compra."<<endl;
            cout<<"\n¿Desea comprar más puntos?"<<endl;
            cout<<"1. Si"<<endl;
            cout<<"2. No"<<endl;
            cout<<"Ingrese su opción: "; cin>>opcion_puntos;
            switch(opcion_puntos){
              case 1:
                system("cls");
                Comprar_Puntos(Usuarios);
                break;
              case 2:
                system("cls");
                cout<<"Volviendo al menú..."<<endl;
                break;
            }
          }

          break;

        case 2:
          cout<<"Volviendo al menú principal"<<endl;
          return Valor_total;
          break;

        default:
          cout<<"Error al ingresar la opción."<<endl;
          break;
     }
    }while(opcion!=2);
  }

  cout<<"No hay articulos en el carrito de compras."<<endl;
  cout<<"Volviendo al menú..."<<endl;

  return Valor_total;
}

// Función para cargar usuarios
int Cargar_Usuarios(sUsuario Usuarios[])
{
  FILE* archivo; //abrir el archivo
  archivo = fopen(RutaArchivoUsuarios,"rb");
  if(archivo != NULL)
  {
    sUsuario usuario;//definir el usuario (buffer de lectura)

    while(fread(&usuario, sizeof(sUsuario), 1, archivo) == 1) //leer el usuario desde el archivo
    {
      Usuarios[Cantidad_Usuarios] = usuario;
      Cantidad_Usuarios++;

    }

    fclose(archivo);//cerrar el archivo
  }

  return Cantidad_Usuarios;
}

// Función para guardar usuarios
void Guardar_Usuarios(sUsuario Usuarios[], int Cantidad_Usuarios)
{
  FILE* archivo;//abrir el archivo
  archivo = fopen(RutaArchivoUsuarios, "wb");//abrir archivo

  if(archivo != NULL)
  {
    for(int i = 0; i < Cantidad_Usuarios; i++) //recorrer los usuarios
    {
      sUsuario usuario = Usuarios[i];//definir el usuario (buffer de escritura)

      fwrite(&usuario, sizeof(sUsuario), 1, archivo);
    }
    fclose(archivo);//cerrar el archivo
  }

}

// Función para cargar productos
int Cargar_Productos(sProductos ListaDeProductos[])
{
  Cantidad_Productos=0;

  FILE* archivo; //abrir el archivo
  archivo = fopen(RutaArchivoProductos,"rb");
  if(archivo != NULL)
  {
    sProductos producto;//definir el usuario (buffer de lectura)
    while(fread(&producto, sizeof(sProductos), 1, archivo) == 1) //leer el usuario desde el archivo
    {
      ListaDeProductos[Cantidad_Productos] = producto;
      Cantidad_Productos++;
    }
    fclose(archivo);//cerrar el archivo
  }
  else
  {
    cout<<"ERROR 404: No se puede abrir el archivo: "<<RutaArchivoProductos<<endl;
    cout<<"Abortando carga de datos"<<endl;
    Cantidad_Productos=-2;
  }

  return Cantidad_Productos;
}