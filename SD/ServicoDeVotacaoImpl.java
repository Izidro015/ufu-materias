import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.HashMap;
import java.util.Map;

public class ServicoDeVotacaoImpl extends UnicastRemoteObject implements ServicoDeVotacao, ServicoDeResultados{
    private Map<String, Integer> contagemVotos;
    protected ServicoDeVotacaoImpl() throws RemoteException {
        super();
        contagemVotos = new HashMap<>();
    }
    public synchronized void votar(String eleitor, String candidato) throws RemoteException {
        contagemVotos.put(candidato, contagemVotos.getOrDefault(candidato, 0) + 1);
        System.out.println("Voto registrado: Eleitor [" + eleitor + "] votou em [" + candidato + "]");
    }
    public synchronized Map<String, Integer> obterResultados() throws RemoteException {
        return new HashMap<>(contagemVotos);
    }
}