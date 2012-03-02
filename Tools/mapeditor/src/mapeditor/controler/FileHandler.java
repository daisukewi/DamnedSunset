/**
 * 
 */
package mapeditor.controler;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;

/**
 * @author Guibrush
 *
 */
public class FileHandler {
	
	private FileOutputStream _fileOutput;
	private FileInputStream _fileInput;

	private FileReader _fileReader;
	private PrintWriter _printWriter;
	
	private ObjectOutputStream _objectOutput;
	private ObjectInputStream _objectInput;
	
	private BufferedReader _bufferedReader;
	
	public FileHandler() {
		
	}
	
	public void saveData(File file, Object data) {
		
		try {
			_fileOutput = new FileOutputStream(file);
			_objectOutput = new ObjectOutputStream(_fileOutput);
			
			_objectOutput.writeObject(data);
			
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	public Object openData(File file) {
		
		try {
			_fileInput = new FileInputStream(file);
			_objectInput = new ObjectInputStream(_fileInput);
			
			return _objectInput.readObject();
			
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}
		
	}
	
	public void initExportData(File file) {
		
		try {
			_printWriter = new PrintWriter(file);
			
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	public void exportData(String data) {
		
		if (_printWriter != null)
			_printWriter.print(data);
		
	}
	
	public void closeExportFile() {
		
		if (_printWriter != null)
			_printWriter.close();
		
	}
	
	public void initImportData(File file) {
		
		try {
			_fileReader = new FileReader(file);
			_bufferedReader = new BufferedReader(_fileReader);
			
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	public String importData() {
		
		try {
			return _bufferedReader.readLine();
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}
		
	}
	
	public void closeImportFile() {
		
		try {
			_fileReader.close();
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

}
