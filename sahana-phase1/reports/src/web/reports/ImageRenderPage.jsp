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
%>

<%= imageData %>

