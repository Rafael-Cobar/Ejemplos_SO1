/*
    Este modulo kernel irá a leer 
    el tiempo actual del sistema
*/

// Dependencias
// Importantes
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>

#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/sysinfo.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/swap.h>
#include <linux/timekeeping.h>

// ******************** Datos del Autor ********************
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rafael Cobar");
MODULE_DESCRIPTION("Modulo Kernel que muestra el tiempo del sistema");
MODULE_VERSION("0.1");

// ****** Funciones ********

// cargar_tiempo = va al kernel y carga el tiempo
static int cargar_tiempo(struct seq_file *archivo, void *v)
{
    // ktime_get_real_seconds = devuelve el tiempo en segundos transcurridos desde 1970
    unsigned long current_time = ktime_get_real_seconds(); // Segundos transcurridos desde 1970

    int seconds, minutes, hours;

    // Calculo de segundos, minutos y horas
    seconds = (current_time % 60);      // Obtener segundos en la hora actual
    minutes = (current_time / 60) % 60; // Obtener minutos en la hora actual
    hours = (current_time / 3600) % 24; // Obtener horas en tiempo actual

    // Imprimir en el archivo
    seq_printf(archivo, "%d:%d:%d\n", hours, minutes, seconds);

    return 0;
}

// escribir_archivo = para escribir en el archivo
static ssize_t
escribir_archivo(struct file *file, const char __user *buffer, size_t count, loff_t *f_pos)
{
    return 0;
}

// abrir_archivo = Para abrir el archivo
static int
abrir_archivo(struct inode *inode, struct file *file)
{
    return single_open(file, cargar_tiempo, NULL);
}

static struct file_operations operaciones = {
    .owner = THIS_MODULE,      // numero que le vamos a asignar
    .open = abrir_archivo,     // funcion que vamos a crear
    .release = single_release, //
    .read = seq_read,          //
    .llseek = seq_lseek,       //
    .write = escribir_archivo  // funcion que vamos a escribir
                               //
};

// fnInicio = se ejecuta al iniciar modulo
static int __init fnInicio(void)
{
    struct proc_dir_entry *entry; // puntero de una estructura

    // timesptamps = nombre del archivo, 0777 = permiso del archivo, &operaciones = funciones
    entry = proc_create("timestamps", 0777, NULL, &operaciones); // creamos una nueva estructura, crea el archivo

    if (!entry)
    {
        return -1; // Existe error
    }
    else
    {
        printk(KERN_INFO "@timestamps-module ,\n Modulo Kernel iniciado\n"); // si lo crea, entonces imprimir
    }

    return 0; // no hubo error
}

// fnExit = finaliza el modulo
static void __exit fnExit(void)
{
    remove_proc_entry("timestamps", NULL);
    printk(KERN_INFO "@timestamps-module,\n Modulo Kernel finalizado\n");
}

// ******************* Funciones importantes *********************
module_init(fnInicio); // se ejecuta al iniciar
module_exit(fnExit);   // se ejecuta para finalizar