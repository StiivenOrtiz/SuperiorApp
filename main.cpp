#include <iostream> //Libreria para entradas y salidas
#include <wchar.h> // poder colocar caracteres especiales
#include <stdlib.h> // gestión de memoria dinámica, control de procesos y otras cosas
#include <string.h> // Librería de manipulación de vectores de char / manipulación de strings

using namespace std;

/*	Se declaran las variables constantes de: La ruta de archivo de los usuarios y productos,
		al igual que el tamaño que van a tener variables como nombres y apellidos y telefonos. */

const char RutaArchivoUsuarios[] = "usuarios.bin";
const char RutaArchivoProductos[] = "productos.bin";
const int Tam_NombresApellidos = 15;
const int Tam_CorreoContrasena = 30;
const int Tam_Telefono = 15;

//	Ahora se declaran las estructuras que van a ser utilizadas en el código, "usuarios, productos, carrito".

struct sUsuario
{
    char Nombre[Tam_NombresApellidos];
    char Apellido[Tam_NombresApellidos];
    char Correo[Tam_CorreoContrasena];
    char Contrasenia[Tam_CorreoContrasena];
    double Saldo;
    char Direccion[100];
    char Genero;
    char FechaNacimiento[8];
} Usuarios[10000]; // Se crea una reserva de 10000 usuarios.

struct sProductos
{
    char Articulo[Tam_NombresApellidos];
    char Categoria[Tam_NombresApellidos];
    char Unidad[Tam_NombresApellidos];
    double Precio;
} ListaDeProductos[20]; // También se crea un arreglo de esta estructura de 20, para dejar una reserva.

struct sCarrito
{
    char Articulo[Tam_NombresApellidos];
    char Categoria[Tam_NombresApellidos];
    char Unidad[Tam_NombresApellidos];
    double Precio;
    int Cantidad;
} Carrito_Compras[30]; // Al igual que en la anterior estructura se crea un arreglo de 50, para tener una reseva en caso de ser más.

/*  Vamos a declarar las variables necesarias para ser utilizadas luego en funciones y asi mismo en el programa, en este caso son los contadores de productos, carrito
    y usuarios. Tambien hacemos la creación de una variable para saber que usuario ingresará.*/

int Cantidad_Usuarios=0;
int Cantidad_Productos=0;
int Cantidad_PCarrito=0;
int Indice_Usuario=-1;

// Ahora se declaran las funciones que van a ser utilizadas en el programa.

void Menu_Inicial(sUsuario Usuarios[]);
bool Iniciar_Sesion(sUsuario Usuarios[]);
int Registrarse(sUsuario Usuarios[], int cant_usuarios);
bool VerificarCorreo(sUsuario Usuarios[], int cant_usuarios);
void Menu_SesionIniciada(sUsuario Usuarios[]);
int Agregar_Al_Carrito();

int main()
{
    setlocale(LC_ALL, ""); // Se hace uso de la función setlocale, para poder usar tildes y carácteres especiales.
    // Este menu sera desplegado para llamar las demas funciones, siendo este la raiz de todo las demas.

    Menu_Inicial(Usuarios);

    return 0;
}
//función del menu inicial
void Menu_Inicial(sUsuario Usuarios[])
{
    int opcion;

    do
    {
        cout<<"Bienvenido a SuperiorApp"<<endl;
        cout<<"1. Iniciar Sesión"<<endl;
        cout<<"2. Registrarse"<<endl;
        cout<<"3. Salir"<<endl;
        cout<<endl;
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

            break;

        case 3:
            cout<<"Gracias, vuelva pronto."<<endl;

            break;

        default:
            cout<<"Error"<<endl;
            cout<<endl;

            break;
        }

    }
    while(opcion!=3);

}

bool Iniciar_Sesion(sUsuario Usuarios[])
{
    // Creación de las variables que se van a utilizar para comparar.
    char Correo[Tam_CorreoContrasena];
    char Contrasenia[Tam_CorreoContrasena];

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
            // Ahora validamos si la contraseña tambien se encuentra.
            if (strcmp(Usuarios[i].Contrasenia, Contrasenia) == 0)
            {
                // En caso de que se encuentre, entonces retornará true
                cout<<"Ha iniciado sesión correctamente."<<endl;
                cout<<endl;
                Indice_Usuario=i;
                return true;
            }
            else
            {
                cout<<"Error principal: La contraseña es incorrecta"<<endl;
            }
        }
    }
    // En caso de no encontrar a el correo, se va a avisar al usuario
    cout<<"El correo no ha sido encontrado (ó la contraseña no coincide)."<<endl;
    cout<<endl;

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

    cout<<"Ingrese su fecha de nacimiento: ";
    cin>>NuevoUsuario.FechaNacimiento;

    Usuarios[cant_usuarios] = NuevoUsuario; // Utilizamos el nuevo usuario para darle agregarlo al arreglo de estructuras.

    cout<<endl;
    cout<<"-Registro exitoso-"<<endl;
    cout<<endl;

    return cant_usuarios+1; // aumentamos uno más para que el arreglo de estructuras aumente.
}

void Menu_SesionIniciada(sUsuario Usuarios[])
{
    int opcion;
    //Mensaje del nombre completo del usuario
    for(int i = 0; i < 1; i++)
    {
        cout<<"Bienvenido: "<<Usuarios[i].Nombre<<" "<<Usuarios[i].Apellido<<endl;
    }

    do
    {
        cout<<"\nPor favor seleccione una opción "<<endl;
        cout<<"1. Agregar al carrito de mercado"<<endl;
        cout<<"2. Modificar carrito de mercada "<<endl;
        cout<<"3. Ver carrito de mercado "<<endl;
        cout<<"4. Pagar carrito de mercado "<<endl;
        cout<<"5. Comprar puntos "<<endl;
        cout<<"6. Consultar saldo "<<endl;
        cout<<"7. Salir"<<endl;
        cout<<"Digite su opción: ";
        cin>>opcion;
    }
    while(opcion != 7);
}
//función para cargar estudiantes
int Cargar_Usuario(sUsuario Usuarios[])
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
        cout<<endl<<"Carga de datos realizada exitosamente"<<endl;
    }
    else
    {
        cout<<"ERROR: No se puede abrir el archivo"<<RutaArchivoProductos<<endl;
        cout<<"Abortando carga de datos"<<endl;
    }
    return Cantidad_Usuarios;
}
//función para guardar estudiantes
void Guardar_Usuario(sUsuario Usuarios[], int Cantidad_Usuarios)
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
        cout<<endl<<"Guardado de datos realizado exitosamente"<<endl;
    }
    else
    {
      cout<<"ERROR: no se pudo abrir el archivo"<<RutaArchivoUsuarios<<endl;
      cout<<"Abortando guardado de datos"<<endl;
    }
}




