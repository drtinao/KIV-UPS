import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;

import static javax.swing.JOptionPane.showMessageDialog;

public class Game {
    private static ArrayList<String> cards = null; /* players cards */
    private static ArrayList<String> playerNames = null; /* names of players in room */
    private static HashMap<String, String> cardWordMap = null; /* HashMap for converting code of card -> name of card */
    private static HashMap<String, String> wordCardMap = null; /* HashMap for converting name of card -> code of card */

    private static JLabel actualPlayerL = null; /* actual player´s name */
    private static JLabel actualColor = null; /* shows actual color of card */
    private static JLabel imageCardActualL = null; /* JLabel with actual pool card */
    private static JLabel imageCardUserL = null; /* JLabel with user card card */

    private static JList userCardList = null; /* JList which contains list of cards which are held by user */
    private static DefaultListModel cardModel = null; /* model used by userCardList */
    private static JList playerList = null; /* JList which contains list of players which are in game */
    private static JComboBox colorCB = null; /* JComboBox with colors */

    private static Game game = null; /* instance of singleton class - Game */
    private static JFrame gameFrame = null; /* JFrame which contains game GUI parts */

    private static JFrame discFrame = null; /* JFrame is dispayed when user disconnects */
    private static JFrame endFrame = null; /* JFrame is displayed when game is over */

    private static boolean playerNamesDisplayed = false; /* true when player names are displayed */
    private static boolean cardsDisplayed = false; /* true when cards are displayed */

    private static AtomicBoolean left = new AtomicBoolean(false); /* true if user left the room */

    /**
     * Sets visibility of Game part.
     * @param visibility true -> game window visible, false -> game window invisible
     */
    public static void setVisibility(boolean visibility){
        if(visibility){
            resetComponent();
        }

        if(game == null){
            game = new Game();
        }

        if(gameFrame == null){
            gameFrame = game.prepGameFrame();
        }

        if(cardWordMap == null){
            initCardWordMap();
        }

        if(wordCardMap == null){
            initWordCardMap();
        }

        gameFrame.setVisible(visibility);
        getCardsHand();
        getPlayerNames();

        startDataSend();
    }

    /**
     * Resets all static variables to default state.
     */
    public static void resetComponent(){
        cards = null; /* actual players cards */
        playerNames = null; /* name of players in room */
        cardWordMap = null; /* code of card -> name of card */
        wordCardMap = null; /* name of card -> code of card */

        actualPlayerL = null; /* actual players name */
        actualColor = null; /* show actual color of card */
        imageCardActualL = null; /* JLabel with actual pool card */
        imageCardUserL = null; /* JLabel with user card card */

        userCardList = null; /* JList which contains list of cards which are held by user */
        cardModel = null; /* model used by userCardList */
        playerList = null; /* JList which contains list of players which are in game */
        colorCB = null; /* JComboBox with colors */

        game = null;
        gameFrame = null;

        discFrame = null; /* frame for disconnected */
        endFrame = null; /* frame for game end */

        playerNamesDisplayed = false; /* true when player names are displayed */
        cardsDisplayed = false; /* true when cards are displayed */

        left = new AtomicBoolean(false); /* true if user left the room, then exit thread */
    }

    /**
     * Sends code request for getting cards which user holds and stores them in ArrayList object.
     */
    public static void getCardsHand(){
        ClientConnection con = ClientConnection.getClientConnection();

        new Thread(() -> {
            String result = con.sendToServer("51", 4, false, true, false);

            if(result.charAt(0) == '#' && result.charAt(33) == '?') { /* ok received */
                result = result.substring(1, 33);

                /* get name of individual cards */
                cards = new ArrayList<>();
                for(int i = 0; i < 32; i++){
                    if(result.charAt(i) == '1'){ /* if card is present */
                        /* get name of card */
                        String cardPos = String.valueOf(i + 1);
                        if(cardPos.length() == 1){ /* add '0' to get right code */
                            cardPos = '0' + cardPos;
                        }

                        System.out.println("Got card " + cardWordMap.get(cardPos));
                        cards.add(cardPos); /* add card code to the list */
                    }
                }

                displayCardsHand();
            }else{
                getCardsHand();
            }
        }).start();
    }

    /**
     * Displays all cards which are currently in user´s hand.
     */
    public static void displayCardsHand(){
        cardModel = new DefaultListModel();
        cardModel.clear();

        for(int i = 0; i < cards.size(); i++){
            cardModel.add(i, cardWordMap.get(cards.get(i)));
        }
        userCardList.setModel(cardModel);
        cardsDisplayed = true;
    }

    /**
     * Prepares object of type JFrame which contains all GUI items of main game window.
     * @return JFrame object with GUI items
     */
    private static JFrame prepGameFrame(){
        JFrame gameFrame = new JFrame("Game");
        gameFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        gameFrame.setLayout(new BoxLayout(gameFrame.getContentPane(), BoxLayout.Y_AXIS));

        gameFrame.add(getUserPanel());
        gameFrame.add(getPoolCardPanel());
        gameFrame.add(getUserCardPanel());
        gameFrame.setSize(500,600);
        gameFrame.setResizable(false);

        gameFrame.setLocationRelativeTo(null);
        return gameFrame;
    }

    /**
     * Prepares object of type JPanel which contains all GUI items regarding to card pool (ie. name of actual player, picture of actual card).
     * @return JPanel object with items regarding to card pool
     */
    private static JPanel getPoolCardPanel(){
        actualColor = new JLabel("Color: same");

        BufferedImage actualCardImg = null;
        try
        {
            actualCardImg = ImageIO.read(new File("karty/empty.jpg"));
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
        ImageIcon imageIcon = new ImageIcon(actualCardImg);
        imageCardActualL = new JLabel();
        imageCardActualL.setIcon(imageIcon);

        JPanel poolCardP = new JPanel();
        poolCardP.setLayout(new BoxLayout(poolCardP, BoxLayout.Y_AXIS));
        poolCardP.add(actualColor);
        poolCardP.add(imageCardActualL);

        poolCardP.setAlignmentX(Component.CENTER_ALIGNMENT);

        return poolCardP;
    }

    /**
     * Prepares object of type JPanel which contains all GUI items regarding to cards, which user currently holds.
     * @return JPanel object with items regarding cards, which user currently holds
     */
    private static JPanel getUserCardPanel(){
        JLabel usCardL = new JLabel("Your cards");
        JLabel changeColorL = new JLabel("Color: ");

        String colors[] = {"koule","cervena","zelena","zaludy"};
        colorCB = new JComboBox(colors);
        colorCB.setEnabled(false);

        JButton placeBtn = new JButton("Place card!");
        placeBtn.addActionListener(e -> performPlaceCard());
        JButton takeSkipBtn = new JButton("Take / skip");
        takeSkipBtn.addActionListener(e -> performTakeStandCard());

        usCardL.setAlignmentX(Component.CENTER_ALIGNMENT);

        BufferedImage userCardImg = null;
        try
        {
            userCardImg = ImageIO.read(new File("karty/empty.jpg"));
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
        ImageIcon imageIconUserC = new ImageIcon(userCardImg);
        imageCardUserL = new JLabel();
        imageCardUserL.setIcon(imageIconUserC);

        userCardList = new JList();
        userCardList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        userCardList.addListSelectionListener(new ListSelectionListener() {
            @Override
            public void valueChanged(ListSelectionEvent e) {
                changeSelectedCardImage();
            }
        });

        JScrollPane sPaneCardList = new JScrollPane(userCardList);
        Dimension d = userCardList.getPreferredSize();
        d.width = 160;
        d.height = 130;
        sPaneCardList.setPreferredSize(d);

        /* put components inside JPanel - START */
        JPanel outerCardP = new JPanel();
        outerCardP.setAlignmentX(Component.CENTER_ALIGNMENT);
        outerCardP.add(usCardL);
        outerCardP.setLayout(new BoxLayout(outerCardP, BoxLayout.Y_AXIS));

        JPanel userCardP = new JPanel();
        userCardP.setAlignmentX(Component.CENTER_ALIGNMENT);
        userCardP.setLayout(new BoxLayout(userCardP, BoxLayout.X_AXIS));
        userCardP.add(sPaneCardList);
        userCardP.add(imageCardUserL);
        outerCardP.add(userCardP);

        JPanel bottomPlaceP = new JPanel();
        bottomPlaceP.setAlignmentX(Component.CENTER_ALIGNMENT);
        bottomPlaceP.setLayout(new BoxLayout(bottomPlaceP, BoxLayout.X_AXIS));
        bottomPlaceP.add(changeColorL);
        bottomPlaceP.add(colorCB);
        bottomPlaceP.add(placeBtn);
        bottomPlaceP.add(takeSkipBtn);
        outerCardP.add(bottomPlaceP);
        /* put components inside JPanel - END */

        return outerCardP;
    }

    /**
     * Changes picture of selected card, according to user choice of card.
     */
    private static void changeSelectedCardImage(){
        BufferedImage actualCardImg = null;
        try
        {
            if(userCardList.getSelectedValue() == null){
                actualCardImg = ImageIO.read(new File("karty/empty.jpg"));
            }else{
                String nameCardSelected = userCardList.getSelectedValue().toString();

                String code = wordCardMap.get(nameCardSelected);
                actualCardImg = ImageIO.read(new File("karty/" + code + ".jpg"));

                if(code.equals("06") || code.equals("14") || code.equals("22") || code.equals("30")){ /* měnič, user can change color */
                    if(!colorCB.isEnabled()){
                        colorCB.setEnabled(true);
                    }
                }else{
                    if(colorCB.isEnabled()){
                        colorCB.setEnabled(false);
                    }
                }
            }
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

        ImageIcon imageIcon = new ImageIcon(actualCardImg);
        imageCardUserL.setIcon(imageIcon);
    }

    /**
     * Get names of players currently present in room.
     */
    public static void getPlayerNames(){
        ClientConnection con = ClientConnection.getClientConnection();

        new Thread(() -> {
            String userNames = con.sendToServer("50", 4, true, false, false);
            if(userNames.charAt(0) == '#' && userNames.charAt(46) == '?'){ /* ok received */
                userNames = userNames.substring(1, 46);

                playerNames = new ArrayList<>();
                int counter = 0;
                for(int i = 0; i < 3; i++){ /* 45 length (3 * 15 for name) */
                    String nameBuffer = "";

                    int j = 0;
                    for(; j < 15; j++){ /* one name */
                        if(userNames.charAt(counter) != '%')
                            nameBuffer += userNames.charAt(counter);
                        counter += 1;
                    }

                    if(!nameBuffer.equals("")){
                        playerNames.add(nameBuffer);
                    }
                }

                displayPlayerNames();
            }else{ /* server returned invalid data, one more time request */
                getPlayerNames();;
            }
        }).start();
    }

    /**
     * Displays all user players which are currently in the room.
     */
    public static void displayPlayerNames(){
        DefaultListModel model = new DefaultListModel();
        model.clear();

        for(int i = 0; i < playerNames.size(); i++){
            model.add(i, playerNames.get(i));
        }
        playerList.setModel(model);
        playerNamesDisplayed = true;
    }

    /**
     * Performs card place to pool.
     */
    private static void performPlaceCard(){
        if(userCardList.getSelectedValue() == null){
            showMessageDialog(null,"Please select card to place!","Warning",JOptionPane.WARNING_MESSAGE);
        }

        ClientConnection con = ClientConnection.getClientConnection();

        String nameCardSelected = userCardList.getSelectedValue().toString();
        int indexSelected = userCardList.getSelectedIndex();
        String code = wordCardMap.get(nameCardSelected);

        if(code.equals("06")){ /* koule měnič */
            if(colorCB.getSelectedItem().toString().equals("koule")){ /* change to koule */
                code = "06";
            }else if(colorCB.getSelectedItem().toString().equals("cervena")){ /* change to červená */
                code = "33";
            }else if(colorCB.getSelectedItem().toString().equals("zelena")){ /* change to zelená */
                code = "34";
            }else{ /* change to žaludy */
                code = "35";
            }
        }else if(code.equals("14")){ /* červená měnič */
            if(colorCB.getSelectedItem().toString().equals("koule")){ /* change to koule */
                code = "36";
            }else if(colorCB.getSelectedItem().toString().equals("cervena")){ /* change to červená */
                code = "14";
            }else if(colorCB.getSelectedItem().toString().equals("zelena")){ /* change to zelená */
                code = "37";
            }else{ /* change to žaludy */
                code = "38";
            }
        }else if(code.equals("22")){ /* zelená měnič */
            if(colorCB.getSelectedItem().toString().equals("koule")){ /* change to koule */
                code = "39";
            }else if(colorCB.getSelectedItem().toString().equals("cervena")){ /* change to červená */
                code = "40";
            }else if(colorCB.getSelectedItem().toString().equals("zelena")){ /* change to zelená */
                code = "22";
            }else{ /* change to žaludy */
                code = "41";
            }
        }else if(code.equals("30")){ /* žaludy měnič */
            if(colorCB.getSelectedItem().toString().equals("koule")){ /* change to koule */
                code = "42";
            }else if(colorCB.getSelectedItem().toString().equals("cervena")){ /* change to červená */
                code = "43";
            }else if(colorCB.getSelectedItem().toString().equals("zelena")){ /* change to zelená */
                code = "44";
            }else{ /* change to žaludy */
                code = "30";
            }
        }

        String finalCode = code;
        new Thread(() -> {
            String response = con.sendToServer(finalCode, 4, false, false, false);

            if(response.equals("#99?")){ /* ok, success, remove card from client */
                cards.remove(indexSelected);
                displayCardsHand();

                BufferedImage actualCardImg = null;
                try
                {
                    actualCardImg = ImageIO.read(new File("karty/empty.jpg"));
                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
                ImageIcon imageIcon = new ImageIcon(actualCardImg);
                imageCardUserL.setIcon(imageIcon);

            }else if(response.equals("#69?")){ /* this card cannot be placed */
                showMessageDialog(null,"This card cannot be placed on previous card!","Warning",JOptionPane.WARNING_MESSAGE);
            }else if(response.equals("#68?")){ /* not users turn to play */
                showMessageDialog(null,"Wait for other player to finish his turn!","Warning",JOptionPane.WARNING_MESSAGE);
            }else if(response.equals("#98?")){
                showMessageDialog(null,"Server received invalid data, try it one more time please.","Warning",JOptionPane.WARNING_MESSAGE);
            }else if(response.equals("#67?")){ /* take 1 card */
                showMessageDialog(null,"Place 7 or take another card (1 remaining for you).","Warning",JOptionPane.WARNING_MESSAGE);
            }else if(response.equals("#66?")){ /* take 2 cards */
                showMessageDialog(null,"Place 7 or take another card (2 remaining for you).","Warning",JOptionPane.WARNING_MESSAGE);
            }else if(response.equals("#65?")){ /* take 3 cards */
                showMessageDialog(null,"Place 7 or take another card (3 remaining for you).","Warning",JOptionPane.WARNING_MESSAGE);
            }else if(response.equals("#64?")){ /* take 4 cards */
                showMessageDialog(null,"Place 7 or take another card (4 remaining for you).","Warning",JOptionPane.WARNING_MESSAGE);
            }else if(response.equals("#63?")){ /* take 5 cards */
                showMessageDialog(null,"Place 7 or take another card (5 remaining for you).","Warning",JOptionPane.WARNING_MESSAGE);
            }else if(response.equals("#62?")){ /* take 6 cards */
                showMessageDialog(null,"Place 7 or take another card (6 remaining for you).","Warning",JOptionPane.WARNING_MESSAGE);
            }else if(response.equals("#61?")){ /* take 7 cards */
                showMessageDialog(null,"Place 7 or take another card (7 remaining for you).","Warning",JOptionPane.WARNING_MESSAGE);
            }else if(response.equals("#60?")){ /* take 8 cards */
                showMessageDialog(null,"Place 7 or take another card (8 remaining for you).","Warning",JOptionPane.WARNING_MESSAGE);
            }else{ /* server returned invalid confirmation.. */
                showMessageDialog(null,"Server returned invalid data, try it one more time please.","Warning",JOptionPane.WARNING_MESSAGE);
            }
        }).start();
    }

    /**
     * Simulates taking card from pool or standing, if actual card is ace.
     */
    private static void performTakeStandCard(){
        ClientConnection con = ClientConnection.getClientConnection();

        new Thread(() -> {
            String response = con.sendToServer("45", 4, false, false, false);

            if(response.equals("#99?")){
                /* ok, stand */
            }else if(response.equals("#78?")){ /* no free cards in the pool */
                showMessageDialog(null,"No free cards in pool, you cannot take another card!","Warning",JOptionPane.WARNING_MESSAGE);
            }else if(response.equals("#79?")){ /* not users turn to play */
                showMessageDialog(null,"Wait for other player to finish his turn!","Warning",JOptionPane.WARNING_MESSAGE);
            }else if(response.equals("#98?")){
                showMessageDialog(null,"Server received invalid data, try it one more time please.","Warning",JOptionPane.WARNING_MESSAGE);
            }else{/* number of card is expected */
                if(response.charAt(0) == '#' && response.charAt(3) == '?'){
                    String cardNum = response.substring(1, 3);
                    int cardNumNum = Integer.parseInt(cardNum);

                    String cardPos = String.valueOf(cardNumNum + 1);
                    if(cardPos.length() == 1){ /* add '0' to get right code */
                        cardPos = '0' + cardPos;
                    }

                    System.out.println("Got card " + cardWordMap.get(cardPos));
                    cards.add(cardPos); /* add card code to the list */
                    cardModel.add(cards.size() - 1, cardWordMap.get(cardPos));
                }else{
                    /* server returned invalid confirmation.. */
                    showMessageDialog(null,"Server returned invalid data, try it one more time please.","Warning",JOptionPane.WARNING_MESSAGE);
                }
            }
        }).start();
    }

    /**
     * Prepares object of type JPanel which contains GUI items which are responsible for displaying player names and actual player.
     * @return JPanel object which displays actual players
     */
    private static JPanel getUserPanel(){
        JLabel playerL = new JLabel("Player list");
        playerL.setAlignmentX(Component.CENTER_ALIGNMENT);
        actualPlayerL = new JLabel("Actual player: ");
        actualPlayerL.setAlignmentX(Component.CENTER_ALIGNMENT);

        playerList = new JList();
        playerList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        JScrollPane sPanePlayerList = new JScrollPane(playerList);
        Dimension d = playerList.getPreferredSize();
        d.width = 160;
        d.height = 130;
        sPanePlayerList.setPreferredSize(d);

        JPanel playerListP = new JPanel();
        playerListP.setAlignmentX(Component.CENTER_ALIGNMENT);
        playerListP.setLayout(new BoxLayout(playerListP, BoxLayout.Y_AXIS));
        playerListP.add(playerL);
        playerListP.add(sPanePlayerList);
        playerListP.add(actualPlayerL);

        return playerListP;
    }

    /**
     * Inits HashMap which will be used for converting codes of cards to normal card names.
     */
    private static void initCardWordMap(){
        cardWordMap = new HashMap<String, String>();

        cardWordMap.put("01", "koule 7");
        cardWordMap.put("02", "koule 8");
        cardWordMap.put("03", "koule 9");
        cardWordMap.put("04", "koule 10");
        cardWordMap.put("05", "koule spodek");
        cardWordMap.put("06", "koule menic");
        cardWordMap.put("07", "koule kral");
        cardWordMap.put("08", "koule eso");
        cardWordMap.put("09", "cervena 7");
        cardWordMap.put("10", "cervena 8");
        cardWordMap.put("11", "cervena 9");
        cardWordMap.put("12", "cervena 10");
        cardWordMap.put("13", "cervena spodek");
        cardWordMap.put("14", "cervena menic");
        cardWordMap.put("15", "cervena kral");
        cardWordMap.put("16", "cervena eso");
        cardWordMap.put("17", "zelena 7");
        cardWordMap.put("18", "zelena 8");
        cardWordMap.put("19", "zelena 9");
        cardWordMap.put("20", "zelena 10");
        cardWordMap.put("21", "zelena spodek");
        cardWordMap.put("22", "zelena menic");
        cardWordMap.put("23", "zelena kral");
        cardWordMap.put("24", "zelena eso");
        cardWordMap.put("25", "zaludy 7");
        cardWordMap.put("26", "zaludy 8");
        cardWordMap.put("27", "zaludy 9");
        cardWordMap.put("28", "zaludy 10");
        cardWordMap.put("29", "zaludy spodek");
        cardWordMap.put("30", "zaludy menic");
        cardWordMap.put("31", "zaludy kral");
        cardWordMap.put("32", "zaludy eso");
        cardWordMap.put("33", "KARTA_KOULE_MENIC_CERVENA");
        cardWordMap.put("34", "KARTA_KOULE_MENIC_ZELENA");
        cardWordMap.put("35", "KARTA_KOULE_MENIC_ZALUDY");
        cardWordMap.put("36", "KARTA_CERVENA_MENIC_KOULE");
        cardWordMap.put("37", "KARTA_CERVENA_MENIC_ZELENA");
        cardWordMap.put("38", "KARTA_CERVENA_MENIC_ZALUDY");
        cardWordMap.put("39", "KARTA_ZELENA_MENIC_KOULE");
        cardWordMap.put("40", "KARTA_ZELENA_MENIC_CERVENA");
        cardWordMap.put("41", "KARTA_ZELENA_MENIC_ZALUDY");
        cardWordMap.put("42", "KARTA_ZALUDY_MENIC_KOULE");
        cardWordMap.put("43", "KARTA_ZALUDY_MENIC_CERVENA");
        cardWordMap.put("44", "KARTA_ZALUDY_MENIC_ZELENA");
    }

    /**
     * Inits HashMap which will be used for converting usual card names to codes of cards.
     */
    private static void initWordCardMap(){
        wordCardMap = new HashMap<>();
        for(Map.Entry<String, String> entry : cardWordMap.entrySet()){
            wordCardMap.put(entry.getValue(), entry.getKey());
        }
    }

    /**
     * Sends data to server when in game room. As pinging character is used "0".
     */
    private static void startDataSend(){
        ClientConnection con = ClientConnection.getClientConnection();

        Runnable pinger = new Runnable(){
            public void run() {
                if(left.get()){
                    return;
                }

                if(!playerNamesDisplayed || !cardsDisplayed){ /* when all used components are ready */
                    return;
                }

                /* nothing to send, just ping and get game state */
                String response = con.sendToServer("0", 4, false, false, true);

                if(response.charAt(0) == '#' && response.charAt(5) == '?'){ /* ok received */
                    String codeCard = ""; /* code for actual card */
                    codeCard += response.charAt(2);
                    codeCard += response.charAt(3);

                    int actualPlayerNum = Integer.parseInt(String.valueOf(response.charAt(1)));
                    if(response.charAt(4) == '2'){ /* no cards */
                        if(endFrame != null && endFrame.isVisible()){
                            return;
                        }
                        left.set(true);

                        /* waiting window creation - START */
                        endFrame = new JFrame("End");
                        endFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                        endFrame.setLayout(new FlowLayout());
                        JLabel winL = new JLabel("Game has ended!");
                        JButton goLobbyBtn = new JButton("Go to lobby");
                        goLobbyBtn.addActionListener(e -> performGoToLobby());
                        JButton quitGameBtn = new JButton("Quit game");
                        quitGameBtn.addActionListener(e -> performQuitGame());

                        endFrame.add(winL);
                        endFrame.add(goLobbyBtn);
                        endFrame.add(quitGameBtn);
                        endFrame.setSize(220,130);
                        endFrame.setResizable(false);
                        endFrame.setLocationRelativeTo(null);

                        endFrame.setVisible(true);

                        if(gameFrame != null && gameFrame.isVisible()){
                            gameFrame.setVisible(false);
                        }

                        if(cards.size() != 0){
                            showMessageDialog(null,"Opponent is the winner :/!","End",JOptionPane.INFORMATION_MESSAGE);
                        }else{
                            showMessageDialog(null,"YOU are the winner, congratulations!","End",JOptionPane.INFORMATION_MESSAGE);
                        }
                        /* waiting window creation - END */
                    }else if(response.charAt(2) == '4' && response.charAt(3) == '6'){ /* user disconnected */
                        if(discFrame != null && discFrame.isVisible()){
                            return;
                        }

                        discFrame = new JFrame("Disconnected");
                        discFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                        discFrame.setLayout(new FlowLayout());
                        JLabel discL = new JLabel("Player disconnected, waiting!");
                        JButton goLobbyBtn = new JButton("Go to lobby");
                        goLobbyBtn.addActionListener(e -> performGoToLobby());
                        JButton quitGameBtn = new JButton("Quit game");
                        quitGameBtn.addActionListener(e -> performQuitGame());

                        discFrame.add(discL);
                        discFrame.add(goLobbyBtn);
                        discFrame.add(quitGameBtn);
                        discFrame.setSize(250,120);
                        discFrame.setResizable(false);

                        discFrame.setLocationRelativeTo(null);
                        discFrame.setVisible(true);
                        gameFrame.setVisible(false);
                    }else{
                        if(discFrame != null && discFrame.isVisible()){
                            discFrame.setVisible(false);
                            gameFrame.setVisible(true);
                        }
                        setActualPlayerName(actualPlayerNum);
                        setPoolCard(codeCard);
                    }
                }else{
                    /* server returned invalid data, wait for another request request */
                }
            }
        };
        ScheduledExecutorService executor = Executors.newScheduledThreadPool(1);
        executor.scheduleAtFixedRate(pinger, 0, 300, TimeUnit.MILLISECONDS);
    }

    /**
     * Sets actual pool card according to code received from server.
     * @param card number of card
     */
    private static void setPoolCard(String card){
        int poolCardNum = Integer.parseInt(card);
        int cardNumNoChange = poolCardNum;
        if(cardNumNoChange > 31 && cardNumNoChange < 35){
            cardNumNoChange = 5; /* koule menic */
        }else if(cardNumNoChange > 34 && cardNumNoChange < 38){
            cardNumNoChange = 13; /* cervena menic */
        }else if(cardNumNoChange > 37 && cardNumNoChange < 41){
            cardNumNoChange = 21; /* zelena menic */
        }else if(cardNumNoChange > 40 && cardNumNoChange < 44){
            cardNumNoChange = 29; /* zaludy menic */
        }

        cardNumNoChange += 1; /* first card on client side is 1 and on server side is 0 */
        String cardToUse = String.valueOf(cardNumNoChange);
        if(cardToUse.length() == 1){
            cardToUse = '0' + cardToUse;
        }

        BufferedImage actualCardImg = null;
        try
        {
            actualCardImg = ImageIO.read(new File("karty/" + cardToUse + ".jpg"));
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

        if(poolCardNum == 5 || poolCardNum == 35 || poolCardNum == 38 || poolCardNum == 41){ /* koule */
            actualColor.setText("Color: koule");
        }else if(poolCardNum == 13 || poolCardNum == 32 || poolCardNum == 39 || poolCardNum == 42){ /* cervena */
            actualColor.setText("Color: cervena");
        }else if(poolCardNum == 21 || poolCardNum == 33 || poolCardNum == 36 || poolCardNum == 43){ /* zelena */
            actualColor.setText("Color: zelena");
        }else if(poolCardNum == 29 || poolCardNum == 34 || poolCardNum == 37 || poolCardNum == 40){ /* zaludy */
            actualColor.setText("Color: zaludy");
        }else{
            actualColor.setText("Color: same");
        }

        ImageIcon imageIcon = new ImageIcon(actualCardImg);
        imageCardActualL.setIcon(imageIcon);
    }

    /**
     * Sets actual player name according to code received from server.
     * @param playerNum number of player which should play.
     */
    private static void setActualPlayerName(int playerNum){
        actualPlayerL.setText("Actual player: " + playerNames.get(playerNum));
    }

    /**
     * Takes user to lobby when other user is disconnected or game has ended.
     */
    private static void performGoToLobby(){
        left.set(true);
        ClientConnection connection = ClientConnection.getClientConnection();

        new Thread(() -> {
            String response = connection.sendToServer("52", 4, false, false, false);
            if(response.equals("#99?")){ /* ok - response */
                if(discFrame != null && discFrame.isVisible()){
                    discFrame.setVisible(false);
                }

                if(endFrame != null && endFrame.isVisible()){
                    endFrame.setVisible(false);
                }

                if(gameFrame != null && gameFrame.isVisible()){
                    gameFrame.setVisible(false);
                }
                Lobby.setVisibility(true);
            }else if(response.equals("#98?")){ /* server received invalid data */
                showMessageDialog(null,"Server received invalid data, try it one more time please.","Warning",JOptionPane.WARNING_MESSAGE);
            }else{/* server returned invalid confirmation.. */
                showMessageDialog(null,"Server returned invalid data, try it one more time please.","Warning",JOptionPane.WARNING_MESSAGE);
            }
        }).start();
    }

    /**
     * Closes game.
     */
    private static void performQuitGame(){
        System.exit(0);
    }
}
