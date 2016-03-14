/*
Autor: Bryan Paul Cortes Renteria
Fecha : 15/Feb/2015
Fecha ultima modificacion: 25/Feb/2015
*/
/*
   Funcion del programa recibe un string, y este se desglosa en caracteres
   cada caracter es convertido a un numero segun su codigo ascii
   luego de esto se almacena su valor en numeros binarios de 8 bits
   correspondientes a cada caracter, para luego tomarlo porciones de 6 bits
   y convertirlas a un numero decimal nuevamente para asi obtener un caracter
   segun la base 64
   al final mostrar los caracteres convertidos en base 64 para el caso el encriptador

   todos estos pasos se realizan de un orden inverso de los pasos para desecnriptar
   pero tiene unos ciertos cambios
//*/
#include <iostream>
#include <stdlib.h>
#include <math.h>
//#include <windows.h>
// error caracteres no imprimibles de ascii
#define ERROR_INPUT_TEXT 01
#define ERROR_NO_ASCII 02
#define ERROR_AVISO_01_DATOS_INCOMPLETOS 03
#define ERROR_BITS_FAIL 04



using namespace std;

// Gestion de interfaz **************************
int menu(); // esta funcion me gestiona lo que debo de recibir y usar las funciones

// ####### INICIO de Logica
//reusables para encriptar y desencriptar
string converbinarioBITS(int a, int bits); // recibe un valor int y lo convierte a binarios con cierta cantiad de bits
string OrdenarAlmacen(int almacen[],int largo); // retorna el almacen ordenado utilizado por la funcion converbinarioBits()
char tablaB64(int a); // tabla de los valores de b64
char TablaAscii(int n); // tabla de referencia para usarla de forma portable entre SO


// solo encriptacion ascii -> b64
string BitsAdecimal64(string buffer, int indice);//se obtiene los binarios (buffer) y se el indice indica para agregar el "="
string bitsB64(string bits);  // 0.1 obtiene los binarios y devuelve los caracteres codificados en base64
string CaracterAbinario(string encode); // se le pasa el texto ascii y devuelve el texto en binarios
int valorAscii(char k); // devuelve el valor de la tabla ASCII correspondinte al caracter


// solo desencriptacion b64 -> ascii
string decodeB64(string almacen); // devuelve los binarios desencriptados de b64
int valorb64(char k); // devuelve valor de la tabla b64 correspondiente al caracter
string BinariosAscii(string binarios); // devuelve el texto descifrado
// ####### FINAL de Logica

//modo debug si se llegara a necesitar (por ahora no sirve pa nada)
void mostrarAlamcen(int almacen[],int largo); // este tambien se podria llamar odenamiento sin mostrar para modificar la variable




int main()
{
   int exit=1;
   while(exit==1)
   {
       try{
      exit=menu();
       }
       catch(int a)
       {
           switch (a)
           {
            case 1:
               cout <<"ERROR CARACTERES NO VALIDOS" << endl;
               cout << endl;
               break;
            case 2:
               cout << "Caracteres No ascii estandar" << endl;
               cout << endl;
            case 3:
               cout << "Aviso 01: Datos Incompletos" << endl;
               cout << endl;
               break;
            case 4:
               cout << "Error Perdida de Bits" << endl;
               cout << endl;
               break;
           }

       }
      cin.get();
      cin.get();
      system("cls"); // Windows
      // system("clear"); // Linux
   }


    cin.get();
    return 0;

}
//============================================
int menu()
{
   string binarios="";
   string binariosDecode="";
   string encode="";
   string texto="";
   string b64="";
   string decode="";
   int op=0;

   cout <<"     Creado por BRYANKER      " << endl;
   cout <<"     Encode/decode b64        " << endl;
   cout << endl;
   cout << "1. Encriptar texto (de texto normal a base 64) " << endl;
   cout << "2. Desencriptar base 64 (base 64 a texto normal)" << endl;
   cout << "3. Salir " << endl;
   cin >> op;
   cin.get();

   switch (op)
   {
   case 1:

    //*/
   cout << endl;
   cout << "introduce el texto porfavor: " << endl;

   getline(cin,texto);

   binarios = CaracterAbinario(texto);
   encode = bitsB64(binarios);
   cout << endl;
   cout << "Texo encriptado: "<< endl;
   cout << endl;
   cout << encode<< endl;

   return 1;
   break;

   case 2:
   cout << endl;
   cout << "introduce el texto Encriptado: " << endl;

   getline(cin,b64);
   binariosDecode = decodeB64(b64);
  /*
   cout << "los Binarios Procesados: " << endl;
   cout << endl;
   cout << binariosDecode << endl;
   cin.get();
   cin.get();
   // Forma debug evaluacion de binarios de texto largo
   //*/
   decode = BinariosAscii(binariosDecode);
   cout << endl;
   cout << "Texo desecnriptado: "<< endl;
   cout << endl;
   cout << decode << endl;
   //cout << binariosDecode << endl;
    return 1;
    break;

   case 3:

    return 0;
    break;

    }
    //*/

}

//============================================


// ******************************************
// reusables para encriptar y desencriptar

// 2 convierte los binarios con cierta cantidad de bits
string converbinarioBITS(int a, int bits)
{

   string resultado; // variable donde se almacena el codigo binario ordenado
   int binario[30]{};
   int posalmacen=0; // variable dinamica para almacenamiento de dato final
   int exit= 0; // variable de salida
   int temp; //variable para almecenar el valor cambiante
   int relleno=0;
   do{
      if (a<0)
      {
         throw  ERROR_NO_ASCII;
         // cambiar por la funcion throw para los errores

      }
      if(a==1)
      {

         binario[posalmacen]= a;
         if(posalmacen>=(bits-1))
         {
            exit = 1;
            break;
         }
         else {

           relleno= (bits-1)-posalmacen; // rellena con ceros a la derecha
                                         // despues de la ordenada quedan a la izquierda

            for(int i=0;i<relleno;i++)
            {
               posalmacen++;
               binario[posalmacen]= 0;
            }
         }

         exit = 1;
         break;
      }else if(a==0)
      {
         binario[posalmacen]= a;
         relleno= (bits-1)-posalmacen; // rellena con ceros a la derecha
                                         // despues de la ordenada quedan a la izquierda

            for(int i=0;i<relleno;i++)
            {
               posalmacen++;
               binario[posalmacen]= 0;
            }
             exit = 1;
         break;
      }

      binario[posalmacen]= (a%2);

      temp= a/2;

      a = temp;
      posalmacen++;


      } while(exit==0);

   resultado = OrdenarAlmacen(binario, posalmacen);

   return resultado;

}

// 3. se le pasa el array que se obtiene de la convercion de decimal a binario para que lo orden
string OrdenarAlmacen(int almacen[],int largo) // ordenamiento returna el almacen ordenado
{
   string orden;
   int a=largo;
   int b=0;
   for(a; a>=0; a--)
   {
      if(almacen[a]==1)
      {
         orden +='1';
      }
      if(almacen[a]==0)
      {
         orden +='0';
      }

      b++;
   }
   return orden;
}


// conversor segun tabla base64 de un decimal indice a base64
char tablaB64(int a)
{

   //de esta forma puedo crear una propia base para obtener encriptar los codigos
   char b; // variable para devolver el caracter correspondiente a base64
   string b64="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  // string b64="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
   b = b64[a];
 return b;

}


char TablaAscii(int n)
{
   char b;
   string TableAscii=" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~��������������Ѫ������������ͦ����ٯ������������";
   b = TableAscii[n];
   return b;
}
//*
// Cierre Funciones Reusables en ambos sentidos
// *******************************************

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// solo encriptacion ascii -> b64

//0.4. se obtiene los binarios y se toma de a 6 bits para poder convertirlos
string BitsAdecimal64(string buffer, int indice)
{
     string codeb64;
   int b=0; // incio de ciclo
   int ciclos=0; // ciclos segun indice
   int Vtemp=0; // valor para convertir a decimal b64
   int Ipow=5; // indice de potencia
   if(indice==23)
   {
      do{
           Ipow=5; // Reincio por obligacion
            Vtemp=0; // reincio por obligacion
          do{

         if(buffer[b]=='1')
         {
            Vtemp += pow(2,Ipow);
            b++;

         }else if(buffer[b]=='0')
         {
            b++;
         }
         Ipow--;
          }while(Ipow>=0);

          codeb64 += tablaB64(Vtemp);// asignacion de caracter de base 64

      ciclos++;
      }while(ciclos<4);
      return codeb64;
   }else if(indice==17)
   {
      do{
            Ipow=5; // Reincio por obligacion
            Vtemp=0; // reincio por obligacion
          do{
         if(buffer[b]=='1')
         {
            Vtemp += pow(2,Ipow);
            b++;
         }else if(buffer[b]=='0')
         {
            b++;
         }
         Ipow--;
          }while(Ipow>=0);
          codeb64 += tablaB64(Vtemp);// asignacion de caracter de base 64
      ciclos++;
      }while(ciclos<3);
      return codeb64;

   }else if(indice==11)
   {
        do{
             Ipow=5; // Reincio por obligacion
            Vtemp=0; // reincio por obligacion
          do{
         if(buffer[b]=='1')
         {
            Vtemp += pow(2,Ipow);
            b++;
         }else if(buffer[b]=='0')
         {
            b++;
         }
         Ipow--;
          }while(Ipow>=0);
          codeb64 += tablaB64(Vtemp);// asignacion de caracter de base 64
      ciclos++;
      }while(ciclos<2);
      return codeb64;
   }

   // Lanzamiento de error por parte de throw
   throw ERROR_BITS_FAIL;

   //return codeb64;

}

// 0.1 obtiene los binarios y devuelve los caracteres codificados en base64
string bitsB64(string bits)
{
   // en esta parte se tiene que tomar de 24 bits para hacer la conversion
   //osea 3 bytes para tener el almacenamiento e ir agregando
   // se toma un buffer de 24 bits osea 3 bytes

   int exit=0;
   int posBits=0; // posicion reiniciable del almacen del buffer
   int posBuffer=0; // posicion incrementable para extraer los valores del almacen bits
   int t=0; // Guarda el tama�o del array bits
   string buffer;
   string b64final;
   t= bits.size();
   do{
   posBuffer=0;
   buffer=""; // liberacion del buffer

   if((t-posBits)>=24)
   {
      for(posBuffer; posBuffer<=23;posBuffer++)
      {
         buffer+=bits[posBits];
         posBits++;
      }
      b64final += BitsAdecimal64(buffer,23);
   }else if((t-posBits)>=16) // en esta parte creo que siempre si es verdad siempre recibe 16
   {
      // entonces se complementa con 0 hasta la posicion sea 17
      for(posBuffer; posBuffer<=15;posBuffer++)
      {
         buffer+=bits[posBits];
         posBits++;
      }
      buffer+='0'; // posicion 16
      buffer+='0';   // posicion 17
      //completa dos osea "00"
      //como condicion de que faltaba un bytes entonces se coloca un "="
      b64final += BitsAdecimal64(buffer,17);
      b64final += '=';
      //OOOOOOOOOOOOOOOOOOOOO salida
      exit =1;
      break;
   } else  if(((t-posBits)<16)and(t-posBits)>=8) // en esta debe de recibir siempre 8
   {
      // entonces se complementa con 0 hasta la posicion sea 11
      for(posBuffer; posBuffer<=7;posBuffer++)
      {
         buffer+=bits[posBits];
         posBits++;
      }

      for(posBuffer;posBuffer<=11;posBuffer++) // completa cuatro osea "0000"
      {
         buffer+='0';
      }

      //como condicion de que faltaba dos (2) bytes entonces se coloca dos "="
      b64final += BitsAdecimal64(buffer,11);
      b64final += '=';
      b64final += '=';
      //OOOOOOOOOOOOOOOOOOOOO salida
      exit =1;
      break;
   } else {
      break;
   }



   }while(exit==0);

   return b64final;
}

// 1. se le pasa el texto ascii y devuelve el texto en binarios
string CaracterAbinario(string encode)
{
    int posicion=0;
    int exit =0;
    int ascii=0;
     // ########################################
   // de Letras a Binarios
   string almacen;
    do{
      if(posicion==encode.size()) // esta funcion pasa caracter por caracter para convertirlo a binario
      {
         cout << endl;
         exit=1;
         break;
      }
      else{

            //������������������������������
            // cambio automatico a basado en tabla
      ascii= valorAscii(encode[posicion]); // conversion automatica de char a int se obtiene el valor ascii


     almacen += converbinarioBITS(ascii,8);

      ascii=0;
      posicion++;
         }

   }while(exit==0);

   return almacen;

}

int valorAscii(char k)
{
    for(int i=0; i<=144; i++)
    {
        if(k==TablaAscii(i))
        {
            return (i+32);
            break;
        }
    }
    throw ERROR_INPUT_TEXT;
}

// Cierre Funciones de Encriptacion ascii -> b64
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


// """""""""""""""""""""""""""""""""""""""""""""
// solo desencriptacion b64 -> ascii

string decodeB64(string almacen)
{
    int del=0; // cantidad de digitos a ignorar
    int ajuste=0; // valor para ajustar los valores binarios sobrantes de la encriptacion
    string buffer; // almacen temporal para obtener todos los binarios
    string buffer2; // alamcen temporal dividido para devolver en la cadena final
    string cadenaFinal; // almacen final con el ajuste aplicado de los binarios sobrantes
    int largo=0; // para el tama�o del almacen
    largo=almacen.size();

    if(almacen[(largo-1)]=='=')
    {
        if(almacen[(largo-2)]=='=')
        {
            ajuste=4;
        }
        else{
            ajuste=2;
        }
    }

    if(ajuste==4)
    {
        largo -=3; // ajuste para no tomar los "=="
    }else if(ajuste==2)
    {
        largo -=2; // ajuste para no tomar el "="
    }else if(ajuste==0)
    {
        largo -=1;
    }

    for(int i=0; i<=largo;i++)
    {

        buffer += converbinarioBITS(valorb64(almacen[i]),6);

    }

    if(ajuste==4)
    {
        del = buffer.size();// se resta 1 para las posiciones y se resta 4 por ajuste binarios
        // #######################
        // Prueba de debug de embes de eliminar 4 eliminar 10
        del -=5; // ajuste aplicado
        //del -=11; // ajuste aplicado

        for(int j=0; j<=del;j++)
        {
            cadenaFinal += buffer[j];
        }

    } else if(ajuste==2)
    {
        del = buffer.size();// se resta 1 para las posiciones y se resta 2 por ajuste binarios
        del -=3; // ajuste aplicado

        for(int j=0; j<=del; j++)
        {
            cadenaFinal +=buffer[j];
        }
    }else if(ajuste==0)
    {
        cadenaFinal=buffer;
    }

    return cadenaFinal;
}



int valorb64(char k)
{
    for(int i=0; i<=63; i++)
    {
        if(k==tablaB64(i))
        {
            return i;
            break;
        }
    }
}

string BinariosAscii(string binarios)
{
    char ascii;
    string decode64;
    int b=0; // inicio ciclo
    int Vtemp=0; // valor para almacenar el valor ascii
    int Ipow=7; // indice de potencia

    // Verficiacion de errores
    if(!((binarios.size()%8)==0))
    {
        //lanzar error interno ose con throw
        // por ahora sera con una impresion grafica
        //cout << "Multiplos incorrectos (%8) no ascii" << endl;

        // ********* throw ERROR_AVISO_01_DATOS_INCOMPLETOS; // como dar el viso sin salir
        cout << endl;
        cout << "AVISO 1: Datos Incompletos " << endl;
        cout << endl;
    }
    //ciclos
    do{
        Ipow=7; // Reinicio Obligatorio
        Vtemp=0; // Reinicio Obligatorio
        do{
            if(binarios[b]=='1')
            {
                Vtemp += pow(2,Ipow);
                b++;
            }else if(binarios[b]=='0')
            {
                b++;
            }
            Ipow--;

            }while(Ipow>=0);

        ascii= TablaAscii((Vtemp-32));
        decode64 +=ascii;

    } while(b<binarios.size());

    return decode64;

}

// Cierre Funciones de Desencriptacion b64 -> ascii
// """""""""""""""""""""""""""""""""""""""""""""



// algo que puede servir para un debug
void mostrarAlmacen(int almacen[],int largo) // Pendiente cambiar a ordenamiento
{

   int a=largo;

   for(a; a>=0; a--)
   {
      cout << almacen[a];

   }

}

