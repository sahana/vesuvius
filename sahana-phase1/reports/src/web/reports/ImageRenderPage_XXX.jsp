<%@ page language="java" %>

<%@ page import="java.util.Iterator" %>
<%@ page import="java.awt.image.RenderedImage" %>
<%@ page import="javax.imageio.stream.MemoryCacheImageOutputStream" %>
<%@ page import="java.util.Date" %>
<%@ page import="java.util.TimeZone" %>
<%@ page import="java.io.BufferedOutputStream" %>
<%@ page import="java.text.SimpleDateFormat" %>
<%@ page import="javax.imageio.ImageIO" %>
<%@ page import="javax.imageio.stream.MemoryCacheImageOutputStream" %>

<%
      byte[] imageData = (byte[]) session.getAttribute("image-data");
      response.setHeader("Content-Type", "image/jpeg");
      response.setHeader("Content-Length", String.valueOf(imageData.length));
      SimpleDateFormat sdf = new SimpleDateFormat("EEE, dd MMM yyyy HH:mm:ss z");
      sdf.setTimeZone(TimeZone.getTimeZone("GMT"));
      response.setHeader("Last-Modified", sdf.format(new Date()));

      /*RenderedImage image = (RenderedImage) session.getAttribute("chart-image");

      ByteArrayOutputStream bout = new ByteArrayOutputStream();
      MemoryCacheImageOutputStream mcOut = new MemoryCacheImageOutputStream(bos);

      System.out.println("getImageContents 1");
      ImageIO.write(image, "jpeg", mcOut);
      System.out.println("getImageContents 2");

      mcOut.flush();

      System.out.println("getImageContents 3");

      bos.flush();
      //bis.close();
      bos.close();
      mcOut.close();
      System.out.println("getImageContents 4");
      */
%>

<%= imageData %>

