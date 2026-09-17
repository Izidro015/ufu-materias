import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Map;

public class ClienteConsulta {
    public static void main(String[] args) {
        try{
            Registry registry = LocateRegistry.getRegistry("localhost", 1099);
            ServicoDeResultados servico = (ServicoDeResultados) registry.lookup("SistemaVotacao");
            Map<String, Integer> resultados = servico.obterResultados();
            System.out.println("Resultado Parcial da Votação");
            resultados.forEach((candidato, votos) -> System.out.println("Candidato: " + candidato + "\nVotos: " + votos + "\n"));
        }catch(Exception e){
            System.err.println("Erro ao consultar resultados: " + e.getMessage());
        }
    }
}