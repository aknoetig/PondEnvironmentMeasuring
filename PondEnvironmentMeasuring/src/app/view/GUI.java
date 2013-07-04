package app.view;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import app.controller.ApplicationState;
import app.controller.Controller;

// Graphical User Interface
//
public class GUI extends JFrame implements ActionListener {

	private static final long serialVersionUID = 1L;

	private Controller controller = null;

	private JMenuBar menubar;
	private JMenu menuFile;
	private JMenuItem menuItemExport;

	private JButton connectButton;

	private JTextField ipTextField1;
	private JTextField ipTextField2;
	private JTextField ipTextField3;
	private JTextField ipTextField4;

	private JTextField portTextField;

	private JTextArea textArea;

	// Constructor
	public GUI() {
		super("Pond Environment Measuring Application");
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.getContentPane().setLayout(new FlowLayout());

		controller = Controller.getInstance();

		initialize();
	}

	// Initialize the GUI, calling other initializeXXX() Methods
	private void initialize() {
		initializeMenu();
		initializeCSV();
		initializeControlPanel();
		initialize_LightChart();
		initialize_TempChart();

		this.pack();
		this.setVisible(true);
	}

	// Initialize the Chart
	private void initialize_LightChart() {

		// Create a simple XY chart
		XYSeries series = new XYSeries("Light Graph");
		series.add(1, 1);
		series.add(1, 2);
		series.add(2, 1);
		series.add(3, 9);
		series.add(4, 10);
		// Add the series to your data set
		XYSeriesCollection dataset = new XYSeriesCollection();
		dataset.addSeries(series);
		// Generate the graph
		JFreeChart chart = ChartFactory.createXYLineChart("XY Chart", // Title
				"Time in Hours", // x-axis Label
				"Light in Lux", // y-axis Label
				dataset, // Dataset
				PlotOrientation.VERTICAL, // Plot Orientation
				true, // Show Legend
				true, // Use tooltips
				false // Configure chart to generate URLs?
				);
		
		ChartPanel chartPanel = new ChartPanel(chart, false);
		chartPanel.setPreferredSize(new Dimension(250, 250));
		this.add(chartPanel, BorderLayout.CENTER);

	}

	// Initialize the Chart
	private void initialize_TempChart() {

		// Create a simple XY chart
		XYSeries series = new XYSeries("Temperature Graph");
		series.add(1, 1);
		series.add(1, 2);
		series.add(2, 1);
		series.add(3, 9);
		series.add(4, 10);
		// Add the series to your data set
		XYSeriesCollection dataset = new XYSeriesCollection();
		dataset.addSeries(series);
		// Generate the graph
		JFreeChart chart = ChartFactory.createXYLineChart("XY Chart", // Title
				"Time in Hours", // x-axis Label
				"Temperature in Celsius", // y-axis Label
				dataset, // Dataset
				PlotOrientation.VERTICAL, // Plot Orientation
				true, // Show Legend
				true, // Use tooltips
				false // Configure chart to generate URLs?
				);
		
		ChartPanel chartPanel = new ChartPanel(chart, false);
		chartPanel.setPreferredSize(new Dimension(250, 250));
		this.add(chartPanel, BorderLayout.CENTER);

	}
	
	// initializes the Controlls
	private void initializeControlPanel() {

		JPanel controlPanel = new JPanel();
		controlPanel.setLayout(new GridLayout(3, 0));

		JPanel ipPanel = new JPanel();
		ipPanel.setLayout(new FlowLayout());
		JLabel ipLabel = new JLabel("IP:");
		ipPanel.add(ipLabel);

		ipTextField1 = new JTextField("127", 3);
		ipTextField1.addActionListener(this);
		ipPanel.add(ipTextField1);
		ipPanel.add(new JLabel(":"));
		ipTextField2 = new JTextField("0", 3);
		ipTextField2.addActionListener(this);
		ipPanel.add(ipTextField2);
		ipPanel.add(new JLabel(":"));
		ipTextField3 = new JTextField("0", 3);
		ipTextField3.addActionListener(this);
		ipPanel.add(ipTextField3);
		ipPanel.add(new JLabel(":"));
		ipTextField4 = new JTextField("1", 3);
		ipTextField4.addActionListener(this);
		ipPanel.add(ipTextField4);
		controlPanel.add(ipPanel);

		JPanel portPanel = new JPanel();
		portPanel.setLayout(new FlowLayout());
		JLabel portLabel = new JLabel("Port:");
		portPanel.add(portLabel);
		portTextField = new JTextField("6789", 8);
		portTextField.addActionListener(this);
		portPanel.add(portTextField);
		controlPanel.add(portPanel);

		connectButton = new JButton("Connect");
		connectButton.addActionListener(this);
		controlPanel.add(connectButton);

		this.add(controlPanel);

	}

	// Initializes the CSV View
	private void initializeCSV() {

		textArea = new JTextArea();
		textArea.setEditable(false);
		textArea.setLineWrap(true);

		JScrollPane scrollPane = new JScrollPane(textArea);
		scrollPane.setPreferredSize(new Dimension(400, 300));

		JPanel csvPanel = new JPanel(new BorderLayout());

		csvPanel.add(scrollPane);
		this.getContentPane().add(csvPanel);
	}

	// initializes the Menu
	private void initializeMenu() {
		menubar = new JMenuBar();
		menuFile = new JMenu("File");
		menuItemExport = new JMenuItem("Export as CSV");

		menuFile.add(menuItemExport);
		menubar.add(menuFile);

		menuItemExport.addActionListener(this);

		this.setJMenuBar(menubar);
	}

	// Action Handler, called on GUI-Input Actions
	public void actionPerformed(ActionEvent evt) {
		Object source = evt.getSource();

		if (source.equals(menuItemExport)) {
			// Menu Item "Export as CSV has been selected"
			if (controller.getState() == ApplicationState.INITIALIZED_WITH_DATA) {
				// Exportable Data is available
				System.out.println("Save as CVS");
				JFileChooser fc = new JFileChooser();
				fc.setFileSelectionMode(JFileChooser.FILES_ONLY);

				if (fc.showSaveDialog(this) == JFileChooser.APPROVE_OPTION) {
					File file = fc.getSelectedFile();
					// save to file
					controller.exportCSV(file);
				}
			} else {
				// No exportable Data is available
				JOptionPane.showMessageDialog(this, "No exportable Data.", "",
						JOptionPane.ERROR_MESSAGE);
			}

		}
		if (source.equals(connectButton)) {
			// Connect Button has been clicked

			int port = Integer.parseInt(portTextField.getText());
			String ip = ipTextField1.getText()+"."
					  + ipTextField2.getText()+"."
					  + ipTextField3.getText()+"."
					  + ipTextField4.getText();

			// call Controller to connect
			boolean result = controller.connect(ip, port);
			if (result) {
				// Data has been read in, updating CSV View
				JOptionPane.showMessageDialog(this, "Data has been read", "",
						JOptionPane.INFORMATION_MESSAGE);
				textArea.setText(controller.getCSVData());
			} else {
				// Connection Failed for some reason
				JOptionPane.showMessageDialog(this, "Connection Failed", "",
						JOptionPane.ERROR_MESSAGE);
			}
		}
	}
}
