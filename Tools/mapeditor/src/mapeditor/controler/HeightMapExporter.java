/**
 * 
 */
package mapeditor.controler;

import java.io.*;
import java.util.TreeSet;
import java.util.Vector;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.AffineTransform;
import java.awt.image.*;
import javax.imageio.*;
import javax.swing.*;

import mapeditor.model.*;
import mapeditor.util.*;

/**
 * @author Danny
 *
 */
public class HeightMapExporter {
	
	int _imageWidth, _imageHeight, _mapWidth, _mapHeight;
	float[][] _currentMap, _maxHeightMap;
	byte[] _fPixels;
	
	private int NUM_PASS = 4;
	private float GROWTH = 2.0f;
	private int HM_RESOLUTION = 32;
	private int NOISE_FREQ = 8;

	
	public HeightMapExporter(int width, int height)
	{
		_imageWidth = width * HM_RESOLUTION;
		_imageHeight = height * HM_RESOLUTION;
		_fPixels = new byte[_imageWidth * _imageHeight];
		
	}
	
	public void ProcessMap (Map map, Preferences currentPref)
	{
		PreprocessMap(map, currentPref);
		
		int i = _imageHeight * _imageWidth - 1;
		for (int y = 0; y < _imageHeight; y++)
			for (int x = 0; x < _imageWidth; x++)
			{
				float noise = PerlinNoise(x, y);
				_fPixels[i--] = (byte) (noise * 255);
			}
	}
	
	public void SaveImageHeightmap (File saveFile)
	{        
        try
        {
        	BufferedImage hmImage = new BufferedImage(_imageWidth, _imageHeight, BufferedImage.TYPE_BYTE_GRAY);
        	WritableRaster wr = hmImage.getRaster();
        	wr.setDataElements(0, 0, _imageWidth, _imageHeight, _fPixels);
        	
            ImageIO.write(hmImage, "png", saveFile);
            
        } catch (IOException ex) {
        	
        }
	}
	
	
	////////////////////////
	//   MAP PROCESSING   
	////////////////////////
	
	private void SaveCurrentMap (Map map, Preferences currentPref)
	{
		_mapWidth = map.getMapWidth();
		_mapHeight = map.getMapHeight();
		
		_currentMap = new float[_mapWidth][_mapHeight];
		_maxHeightMap = new float[_mapWidth][_mapHeight];
		
		for (int y = 0; y < _mapHeight; y++)
			for (int x = 0; x < _mapWidth; x++)
			{
				String paramValue = currentPref.getCellParameter(
						map.getCell(new Position(x, y)).getType(),
						"height");
				_currentMap[x][y] = Float.parseFloat(paramValue) / 255.0f;
				
				paramValue = currentPref.getCellParameter(
						map.getCell(new Position(x, y)).getType(),
						"max_height");
				_maxHeightMap[x][y] = Float.parseFloat(paramValue) / 255.0f;
			}
	}

	private void PreprocessMap (Map map, Preferences currentPref)
	{
		SaveCurrentMap(map, currentPref);
		
		for (int pass = 0; pass < NUM_PASS; pass++)
			for (int y = 0; y < _mapHeight; y++)
				for (int x = 0; x < _mapWidth; x++)
				{
					boolean needsGrow = true;
					if (y > 0 && _currentMap[x][y-1] < _currentMap[x][y]) needsGrow = false;
					if (x > 0 && _currentMap[x-1][y] < _currentMap[x][y]) needsGrow = false;
					if (y < _mapHeight-1 && _currentMap[x][y+1] < _currentMap[x][y]) needsGrow = false;
					if (x < _mapWidth-1 && _currentMap[x+1][y] < _currentMap[x][y]) needsGrow = false;
					
					if (needsGrow) _currentMap[x][y] = Math.min(_currentMap[x][y] * GROWTH, _maxHeightMap[x][y]);

				}
	}
	
	private Position GetMapPosition(int x, int y)
	{
		int relX = x * _mapWidth / _imageWidth;
		int relY = y * _mapHeight / _imageHeight;
		
		return new Position(relX, relY);
	}
	
	private int GetMapWidthRelation()
	{
		return _imageWidth / _mapWidth;
	}
	
	private int GetMapHeightRelation()
	{
		return _imageHeight / _mapHeight;
	}
	
	private float GetCellHeight(int x, int y)
	{
		Position pos = GetMapPosition(x, y);
		return _currentMap[pos.getX()][pos.getY()];
	}
	
	private float GetSoftHeight(int x, int y)
	{
		int x0, x1, y0, y1;
		int wRel = GetMapWidthRelation();
		int hRel = GetMapHeightRelation();
		
		Position pos = GetMapPosition(x, y);
		
		x0 = pos.getX() * wRel + wRel/2;
			if (x < x0) x0 -= wRel;
		y0 = pos.getY() * hRel + hRel/2;
			if (y < y0) y0 -= hRel;
		x1 = x0 + wRel;
		y1 = y0 + hRel;
		
		if (x0 < 0) x0 += wRel/2;
		if (y0 < 0) y0 += hRel/2;
		if (x1 >= _imageWidth) x1 -= wRel/2 + 1;
		if (y1 >= _imageHeight) y1 -= hRel/2 + 1;
		
		float a = EaseCurveInterpolate(
				GetCellHeight(x0, y0),
				GetCellHeight(x1, y0),
				(x - x0) / (float)wRel);
		float b = EaseCurveInterpolate(
				GetCellHeight(x0, y1),
				GetCellHeight(x1, y1),
				(x - x0) / (float)wRel);
		
		float height = EaseCurveInterpolate( a, b, (y - y0) / (float)hRel);
		
		return height;
	}
	
	
	/////////////////////////
	//   PERLIN ALGORITHM   
	/////////////////////////
	
	private float PerlinNoise (int x, int y)
	{
		//TODO: Implement Perlin algorithm to add noise
		// 1. Get grid square vertices for the given coordinate.
		// 2. Generate the gradient vectors for the vertices.
		// 3. Get the weight of each vertex
		/*  s = g(x0, y0) · ((x, y) - (x0, y0))
			t = g(x1, y0) · ((x, y) - (x1, y0))
			u = g(x0, y1) · ((x, y) - (x0, y1))
			v = g(x1, y1) · ((x, y) - (x1, y1))
		 */
		// 4. Interpolate the values to get the height of the point.
		
		return GetSoftHeight(x, y);
		//return GetCellHeight(x, y);
	}
	
	
	
	////////////////////////
	//   MATH FUNCTIONS   
	////////////////////////
	
	private double Noise (int x, int y)
	{
		long n = x + y * 57;
		n = (long) Math.pow((n << 13), n);
		
		return (1.0d - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7FFFFFFF) / 1073741824.0d);
	}
	
	private float LinearInterpolate (float a, float b, float x)
	{
		return a + x * (b-a);
	}
	
	private float CosInterpolate (float a, float b, float x)
	{
		float ft = (float) (x * Math.PI);
		float f = (float) ((1 - Math.cos(ft)) * 0.5);
		
		return LinearInterpolate(a, b, f);
	}
	
	private float EaseCurveInterpolate (float a, float b, float x)
	{
		float sx = (float) (3 * Math.pow(x, 2) - 2 * Math.pow(x, 3));
		
		return LinearInterpolate(a, b, sx);
	}

}
