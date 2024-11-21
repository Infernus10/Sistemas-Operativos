
import java.util.Scanner;

/**
 *
 * @author bruno
 */
public class Hospital {

    public static void main(String[] args) {
        Scanner lector = new Scanner(System.in);
        ListaPacientes listaPacientes = new ListaPacientes();

        listaPacientes.agregarPaciente(new Paciente("Juan Perez", 2));
        listaPacientes.agregarPaciente(new Paciente("Ana Gomez", 1));
        listaPacientes.agregarPaciente(new Paciente("Luis Torres", 3));
        listaPacientes.agregarPaciente(new Paciente("Maria Lopez", 1));

        int opcion;
        do{
        System.out.println("¿Qué desea hacer? mostrar pacientes(1) / atender paciente(2) / Salir(0)");
        opcion = lector.nextInt();
        if(opcion == 1){
            listaPacientes.mostrarPacientes();
        }
        if(opcion == 2){
            listaPacientes.atenderPaciente();
        }
        }while(opcion != 0);
        
        
    }
}
