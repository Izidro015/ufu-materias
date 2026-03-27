public class Carta implements Comparable<Carta> {
    public enum Naipe {
        PAUS, COPAS, ESPADAS, OUROS
    }

    public enum Valor {
        QUATRO(1), CINCO(2), SEIS(3), SETE(4), DAMA(5), VALETE(6),
        REI(7), AS(8), DOIS(9), TRES(10),
        SETE_OUROS(11), AS_ESPADAS(12), SETE_COPAS(13), QUATRO_PAUS(14);

        private final int forca;

        Valor(int forca) {
            this.forca = forca;
        }

        public int getForca() {
            return forca;
        }
    }

    private Naipe naipe;
    private Valor valor;
    private int forcaEfetiva;

    public Carta(Naipe naipe, Valor valor) {
        this.naipe = naipe;
        this.valor = valor;
        calcularForcaEfetiva();
    }

    private void calcularForcaEfetiva() {
        if (valor == Valor.QUATRO && naipe == Naipe.PAUS) {
            forcaEfetiva = 14;
        } else if (valor == Valor.SETE && naipe == Naipe.COPAS) {
            forcaEfetiva = 13;
        } else if (valor == Valor.AS && naipe == Naipe.ESPADAS) {
            forcaEfetiva = 12;
        } else if (valor == Valor.SETE && naipe == Naipe.OUROS) {
            forcaEfetiva = 11;
        } else {
            switch (valor) {
                case TRES: forcaEfetiva = 10; break;
                case DOIS: forcaEfetiva = 9; break;
                case AS: forcaEfetiva = 8; break;
                case REI: forcaEfetiva = 7; break;
                case VALETE: forcaEfetiva = 6; break;
                case DAMA: forcaEfetiva = 5; break;
                case SETE: forcaEfetiva = 4; break;
                case SEIS: forcaEfetiva = 3; break;
                case CINCO: forcaEfetiva = 2; break;
                case QUATRO: forcaEfetiva = 1; break;
                default: forcaEfetiva = valor.getForca();
            }
        }
    }

    @Override
    public int compareTo(Carta outra) {
        return Integer.compare(this.forcaEfetiva, outra.forcaEfetiva);
    }

    @Override
    public String toString() {
        String nomeValor = "";
        switch (valor) {
            case QUATRO: nomeValor = "4"; break;
            case CINCO: nomeValor = "5"; break;
            case SEIS: nomeValor = "6"; break;
            case SETE: nomeValor = "7"; break;
            case DAMA: nomeValor = "Q"; break;
            case VALETE: nomeValor = "J"; break;
            case REI: nomeValor = "K"; break;
            case AS: nomeValor = "A"; break;
            case DOIS: nomeValor = "2"; break;
            case TRES: nomeValor = "3"; break;
        }

        String simboloNaipe = "";
        switch (naipe) {
            case PAUS: simboloNaipe = "♣"; break;
            case COPAS: simboloNaipe = "♥"; break;
            case ESPADAS: simboloNaipe = "♠"; break;
            case OUROS: simboloNaipe = "♦"; break;
        }

        String especial = "";
        if (valor == Valor.QUATRO && naipe == Naipe.PAUS) especial = " (Zape)";
        else if (valor == Valor.AS && naipe == Naipe.ESPADAS) especial = " (Espadilha)";
        else if (valor == Valor.SETE && naipe == Naipe.COPAS) especial = " (Ouro)";
        else if (valor == Valor.SETE && naipe == Naipe.OUROS) especial = " (Picafumo)";

        return nomeValor + simboloNaipe + especial;
    }

    public int getForcaEfetiva() { return forcaEfetiva; }
}