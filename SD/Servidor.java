import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Servidor {
    public static void main(String[] args) {
        try{
            ServicoDeVotacaoImpl servico = new ServicoDeVotacaoImpl();
            // Inicia o registro RMI na porta padrão 1099
            Registry registry = LocateRegistry.createRegistry(1099);
            // Registra o objeto sob um nome único
            registry.rebind("SistemaVotacao", servico);
            System.out.println("Servidor de Votação UFU pronto.");
        }catch(Exception e){
            System.err.println("Erro no servidor: " + e.toString());
            e.printStackTrace();
        }
    }
}