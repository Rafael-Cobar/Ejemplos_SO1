#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h> // lista los procs
#include <linux/sched.h> // lista de tareas que tenemos
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/sysinfo.h> // Nos devuelve información del sistema
#include <linux/seq_file.h> // imprimir en consola
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/swap.h> // acceso al swap 
#include <linux/timekeeping.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rafael - Cobar");
MODULE_DESCRIPTION("Modulo que muestra la hora del sistema");
MODULE_VERSION("0.01");

/*
    escribir_a_proc = función para escribir en el archivo abierto
*/
static int escribir_a_proc(struct seq_file *file_proc, void *v) {       

    unsigned long current_time = ktime_get_real_seconds(); // Segundos transcurridos desde 1970
    int seconds, minutes, hours;

    seconds = (current_time % 60);      // Obtener segundos en la hora actual
    minutes = (current_time / 60) % 60; // Obtener minutos en la hora actual
    hours = (current_time / 3600) % 24; // Obtener horas en tiempo actual

    seq_printf(file_proc,"{\"timestamp\":\"%d:%d:%d\"}\n", hours, minutes, seconds); // Imprime en consola la hora
    
    return 0;
}

/*
    abrir_aproc = función que abre el archivo
*/
static int abrir_aproc(struct inode *inode, struct  file *file) {
  return single_open(file, escribir_a_proc, NULL);
}

/*
    archivo_operaciones = es un estructura
*/
static struct proc_ops archivo_operaciones = {    
    .proc_open = abrir_aproc,
    .proc_read = seq_read
};

/*
    modulo_c3_init = crear el archivo y muestra un mensaje
*/
static int __init modulo_c3_init(void) {
    proc_create("timestamps", 0, NULL, &archivo_operaciones); // Crea el archivo "timestamps"
    printk(KERN_INFO "Hola Mundo, Se Creo el Modulo Kernel timestamps\n"); // imprime información en consola

    return 0;
}
 
/*
    modulo_c3_cleanup = elimnina el modulo de los procs
*/
static void __exit modulo_c3_cleanup(void){
    remove_proc_entry("timestamps", NULL);    
    printk(KERN_INFO "El módulo fue RETIRADO\n");
}

/*
    module_init = Función principal y la primera que se ejecutara
    modulo_c3_init = función que se va a ejecutar
*/
module_init(modulo_c3_init);

/*
    module_exit = para eliminar el modulo
*/
module_exit(modulo_c3_cleanup); 