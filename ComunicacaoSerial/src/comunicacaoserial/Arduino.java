package comunicacaoserial;

import javax.swing.JButton;

/**
 * @author klauder
 */
public class Arduino {
  private ControlePorta serial;
  
  /**
   * Construtor da classe Arduino
   */
  public Arduino(){
      serial = new ControlePorta("COM3",9600);//Windows - porta e taxa de transmissão
      //arduino = new ControlePorta("/dev/ttyUSB0",9600);//Linux - porta e taxa de transmissão
  }    

  /**
   * Envia o comando para a porta serial
   * @param button - Botão que é clicado na interface Java
   */
  public void comunicacaoArduino(int opt, int val) {
      
    switch(opt){
        case 0:
            serial.enviaDados(val);
            break;
        case 1:
            serial.enviaDados(val);
            break;
    }
    
    System.out.println("Enviou: "+val);//Imprime o nome do botão pressionado
    
    /*
    if(button == 0){
      arduino.enviaDados(1);
      System.out.println("Ligar");//Imprime o nome do botão pressionado
    }
    else if(button == 1){
      arduino.enviaDados(2);
      System.out.println("Desligar");
    }
    else{
      arduino.close();
      System.out.println("Sair");//Imprime o nome do botão pressionado
      System.exit(0);
    }
    */
  }
}