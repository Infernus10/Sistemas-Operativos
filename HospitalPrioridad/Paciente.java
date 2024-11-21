
/**
 *
 * @author bruno
 */
public class Paciente {
    private String nombre;
    private int prioridad; 

    public Paciente(String nombre, int prioridad) {
        this.nombre = nombre;
        this.prioridad = prioridad;
    }

    public String getNombre() {
        return nombre;
    }

    public int getPrioridad() {
        return prioridad;
    }

    @Override
    public String toString() {
        return "Paciente: " + nombre + ", Prioridad: " + prioridad;
    }
}
