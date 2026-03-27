import java.io.*;
import java.util.*;

public class Dupla implements Serializable {
    private static final long serialVersionUID = 1L;
    private String nome;
    private Jogador jogador1;
    private Jogador jogador2;
    private int pontos;
    private int jogosGanhos;
    private int quedas;
    private int quedasGanhas;
    private int id;

    public Dupla(String nome, Jogador jogador1, Jogador jogador2, int id) {
        this.nome = nome;
        this.jogador1 = jogador1;
        this.jogador2 = jogador2;
        this.pontos = 0;
        this.jogosGanhos = 0;
        this.quedas = 0;
        this.quedasGanhas = 0;
        this.id = id;
    }

    public Dupla(String nome, int id) {
        this.nome = nome;
        this.id = id;
        this.pontos = 0;
        this.jogosGanhos = 0;
        this.quedas = 0;
        this.quedasGanhas = 0;
    }

    public void adicionarPontos(int pontos) {
        this.pontos += pontos;
        if (this.pontos >= 12) {
            this.pontos = 12;
        }
    }

    public boolean ganhouJogo() {
        return pontos >= 12;
    }

    public void ganharJogo() {
        jogosGanhos++;
        pontos = 0;
    }

    public boolean ganhouQueda() {
        return jogosGanhos >= 2;
    }

    public void ganharQueda() {
        quedasGanhas++;
        quedas++;
        resetarQueda();
    }

    public void perderQueda() {
        quedas++;
        resetarQueda();
    }

    private void resetarQueda() {
        jogosGanhos = 0;
        pontos = 0;
    }

    public boolean estaNaMaoDeDez() {
        return pontos == 10;
    }

    public List<Jogador> getJogadores() {
        List<Jogador> jogadores = new ArrayList<>();
        if (jogador1 != null) jogadores.add(jogador1);
        if (jogador2 != null) jogadores.add(jogador2);
        return jogadores;
    }

    public static List<Dupla> carregarDuplas(String arquivo) throws IOException {
        List<Dupla> duplas = new ArrayList<>();
        File file = new File(arquivo);

        if (!file.exists()) {
            return duplas;
        }

        try (BufferedReader reader = new BufferedReader(new FileReader(arquivo))) {
            String linha;
            while ((linha = reader.readLine()) != null) {
                try {
                    Dupla dupla = parsearLinha(linha);
                    if (dupla != null) {
                        duplas.add(dupla);
                    }
                } catch (Exception e) {
                    System.err.println("Erro ao parsear linha: " + linha);
                }
            }
        }

        return duplas;
    }

    private static Dupla parsearLinha(String linha) {//deixar tudo legivel pra maquina
        String[] partes = linha.split(" - ");
        if (partes.length >= 5) {
            try {
                String nome = partes[0].substring(partes[0].indexOf(":") + 2);
                String quedaStr = partes[1].substring(partes[1].indexOf(":") + 2);
                String[] quedaParts = quedaStr.split("/");
                int quedasGanhas = Integer.parseInt(quedaParts[0]);
                int quedas = Integer.parseInt(quedaParts[1]);

                int jogosGanhos = Integer.parseInt(partes[2].substring(partes[2].indexOf(":") + 2));
                int pontos = Integer.parseInt(partes[3].substring(partes[3].indexOf(":") + 2));
                int id = Integer.parseInt(partes[4].substring(partes[4].indexOf(":") + 2));

                Dupla dupla = new Dupla(nome, id);
                dupla.quedas = quedas;
                dupla.quedasGanhas = quedasGanhas;
                dupla.jogosGanhos = jogosGanhos;
                dupla.pontos = pontos;

                return dupla;
            } catch (NumberFormatException | StringIndexOutOfBoundsException e) {
                return null;
            }
        }
        return null;
    }

    public double getPorcentagemVitorias() {
        return quedas > 0 ? (double) quedasGanhas / quedas * 100 : 0;
    }

    @Override
    public String toString() {
        return String.format("Nome: %s - Quedas: %d/%d - Jogos: %d - Pontos: %d - ID: %d",
                nome, quedasGanhas, quedas, jogosGanhos, pontos, id);
    }

    public String toStringDetalhado() {
        return String.format("%s\nJogadores: %s e %s\nQuedas ganhas: %d de %d (%.1f%%)\nJogos ganhos na queda atual: %d\nPontos no jogo atual: %d",
                nome,
                jogador1 != null ? jogador1.getNome() : "N/A",
                jogador2 != null ? jogador2.getNome() : "N/A",
                quedasGanhas, quedas, getPorcentagemVitorias(),
                jogosGanhos, pontos);
    }

    public String getNome() { return nome; }
    public Jogador getJogador1() { return jogador1; }
    public Jogador getJogador2() { return jogador2; }
    public int getPontos() { return pontos; }
    public int getJogosGanhos() { return jogosGanhos; }
    public int getId() { return id; }
    public void setPontos(int pontos) { this.pontos = pontos; }
    public void setJogosGanhos(int jogosGanhos) { this.jogosGanhos = jogosGanhos; }
}