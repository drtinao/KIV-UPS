import javax.swing.*;
import java.awt.*;
import java.text.Normalizer;
import java.util.regex.Pattern;

import static javax.swing.JOptionPane.showMessageDialog;

public class Connect{
    private static JTextField ipTf = null; /* user submitted server IP */
    private static JTextField portTf = null; /* user submitted server number */
    private static JTextField nickTf = null; /* user submitted nick */

    private static Connect connect = null; /* instance of this singleton class */
    private static JFrame connectFrame = null; /* JFrame which contains GUI parts that help with connection to server */

    /**
     * Sets visibility of connect game part.
     * @param visibility true -> connect window visible, false -> connect window invisible
     */
    public static void setVisibility(boolean visibility){
        if(connect == null){
            connect = new Connect();
        }

        if(connectFrame == null){
            connectFrame = connect.prepConnectFrame();
        }

        connectFrame.setVisible(visibility);
    }

    /**
     * Prepares object of type JFrame which contains all GUI items of main connect window.
     * @return JFrame object with GUI items
     */
    private static JFrame prepConnectFrame(){
        JFrame connectFrame = new JFrame("Connect to server");
        connectFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        connectFrame.setLayout(new BorderLayout());

        /* prepare GUI items - START */
        JLabel ipL = new JLabel("IP: ");
        JLabel portL = new JLabel("Port: ");
        JLabel nickL = new JLabel("Nick: ");

        ipTf = new JTextField("", 20);
        ipTf.setToolTipText("Enter server IP");
        portTf = new JTextField("", 20);
        portTf.setToolTipText("Enter port number");
        nickTf = new JTextField("", 20);
        nickTf.setToolTipText("Enter your nick (15 char max)");

        JButton connectBtn = new JButton("Connect!");
        connectBtn.addActionListener(e -> submitValues());
        /* prepare GUI items - END */

        /* prepare JPanels with layout - START */
        JPanel ipP = new JPanel();
        ipP.setLayout(new BoxLayout(ipP, BoxLayout.LINE_AXIS));
        ipP.add(ipL);
        ipP.add(ipTf);

        JPanel portP = new JPanel();
        portP.setLayout(new BoxLayout(portP, BoxLayout.LINE_AXIS));
        portP.add(portL);
        portP.add(portTf);

        JPanel nickP = new JPanel();
        nickP.setLayout(new BoxLayout(nickP, BoxLayout.LINE_AXIS));
        nickP.add(nickL);
        nickP.add(nickTf);

        JPanel mainP = new JPanel();
        mainP.setLayout(new BoxLayout(mainP, BoxLayout.PAGE_AXIS));
        mainP.add(nickP);
        mainP.add(ipP);
        mainP.add(portP);
        /* prepare JPanels with layout - END */

        connectFrame.add(mainP, BorderLayout.CENTER);
        connectFrame.add(connectBtn, BorderLayout.SOUTH);
        connectFrame.setSize(400,150);
        connectFrame.setResizable(false);

        connectFrame.setLocationRelativeTo(null);

        return connectFrame;
    }

    /**
     * Is used for parsing user entered data and sending them to the server. Data check is performed before send.
     */
    private static void submitValues(){
        if(checkValues() != 0){
            return;
        }

        /* input values are ok */
        ClientConnection connection = ClientConnection.getClientConnection();
        connection.initConnection(ipTf.getText(), Integer.valueOf(portTf.getText()));

        if(!connection.getConnectSuccess()){
            if(connection.tryConnect() == 0){
                /* send nickname to server - START */
                String userNick = nickTf.getText();
                int userNickLength = userNick.length();
                if(userNickLength < 15){ /* add "%" to comply with 15 characters requirement */
                    int toAdd = 15 - userNickLength;

                    for(int i = 0; i < toAdd; i++){
                        userNick = userNick.concat("%");
                    }
                }
                System.out.println("Sending: " + userNick);

                /* wait for server response - another thread */
                String finalUserNick = userNick;
                new Thread(() -> {
                    String result = connection.sendToServer(finalUserNick, 1, false, false, false);
                    /* send nickname to server - END */

                    /* go to lobby screen */
                    if(result.equals("#99?")){
                        Lobby.setVisibility(true);
                        Connect.setVisibility(false);
                    }else if(result.equals("#98?")){
                        showMessageDialog(null,"Server received invalid data, try it one more time please.","Warning",JOptionPane.WARNING_MESSAGE);
                    }else{ /* server returned invalid confirmation.. */
                        showMessageDialog(null,"Server returned invalid data, try it one more time please.","Warning",JOptionPane.WARNING_MESSAGE);
                    }
                }).start();
            }
        }
    }

    /**
     * Checks if user entered data are valid (ie.: nick - 15 char max, ip address - 15 char max, port - 5 char max).
     * If there is something wrong, then input is cleared and error message is shown.
     * @return 0 if values are ok, else -1
     */
    private static int checkValues(){
        /* check nick - START */
        if(nickTf == null || nickTf.getText().length() > 15){
            showMessageDialog(new JFrame(), "Nickname length can be 15 characters only!", "Check nickname", JOptionPane.ERROR_MESSAGE);
            if(nickTf != null){
                nickTf.setText("");
            }
            return 1;
        }

        if(nickTf.getText().length() == 0){
            showMessageDialog(new JFrame(), "Nickname cannot be empty!", "Check nickname", JOptionPane.ERROR_MESSAGE);
            if(nickTf != null){
                nickTf.setText("");
            }
            return 1;
        }


        String convertedString = Normalizer.normalize(nickTf.getText(), Normalizer.Form.NFD).replaceAll("[^\\p{ASCII}]", "");
        if(!convertedString.equals(nickTf.getText())){
            showMessageDialog(new JFrame(), "Nickname cannot contain diacritics!", "Check nickname", JOptionPane.ERROR_MESSAGE);
            return 1;
        }

        if(nickTf.getText().contains("%")){
            showMessageDialog(new JFrame(), "Nickname cannot contain \"%\"!", "Check nickname", JOptionPane.ERROR_MESSAGE);
            return 1;
        }

        if(!Pattern.matches("[a-zA-Z0-9]+", nickTf.getText())){
            showMessageDialog(new JFrame(), "Nickname can contain just normal alphabet characters (a-z) and numbers (0-9)!", "Check nickname", JOptionPane.ERROR_MESSAGE);
            return 1;
        }
        /* check nick - END */

        /* check ip - START */
        if(ipTf == null || ipTf.getText().length() > 15){
            showMessageDialog(new JFrame(), "IP length can be 15 characters only!", "Check IP", JOptionPane.ERROR_MESSAGE);
            if(ipTf != null){
                ipTf.setText("");
            }
            return 1;
        }

        if(ipTf.getText().length() == 0){
            showMessageDialog(new JFrame(), "IP cannot be empty!", "Check IP", JOptionPane.ERROR_MESSAGE);
            if(ipTf != null){
                ipTf.setText("");
            }
            return 1;
        }

        String[] splittedIp = ipTf.getText().split("\\.");
        if(splittedIp.length != 4){
            showMessageDialog(new JFrame(), "Wrong IP format!", "Check IP", JOptionPane.ERROR_MESSAGE);
            return 1;
        }

        int i = 0;
        for(; i < splittedIp.length; i++){
            if(!Pattern.matches("[0-9]+", splittedIp[i])){
                showMessageDialog(new JFrame(), "Wrong IP format!", "Check IP", JOptionPane.ERROR_MESSAGE);
                return 1;
            }
        }
        /* check ip - END */

        /* check port - START */
        if(portTf == null || portTf.getText().length() > 5){
            showMessageDialog(new JFrame(), "Port length can be 5 characters only!", "Check port", JOptionPane.ERROR_MESSAGE);
            if(portTf != null){
                portTf.setText("");
            }
            return 1;
        }

        if(portTf.getText().length() == 0){
            showMessageDialog(new JFrame(), "Port cannot be empty!", "Check port", JOptionPane.ERROR_MESSAGE);
            if(portTf != null){
                portTf.setText("");
            }
            return 1;
        }

        if(!Pattern.matches("[0-9]+", portTf.getText())){
            showMessageDialog(new JFrame(), "Port can contain only numbers (0-9)!", "Check port", JOptionPane.ERROR_MESSAGE);
            return 1;
        }
        /* check port - END */

        return 0;
    }
}
