<?xml version="1.0" encoding="UTF-8"?>
<xs:stylesheet xmlns:xs="http://www.w3.org/1999/XSL/Transform" xmlns:cap="urn:oasis:names:tc:emergency:cap:1.1" xmlns:str="http://xsltsl.org/string" version="1.0">
	
    <xs:output method="html"/>
	
    <!-- Alert block -->
	
    <xs:template match="cap:alert">
        <html>
            <head>
                <title>CAP Message</title>
                <style type="text/css">
				
                    body { background-color:#eeeeee;}
                    * { text-align: left; valign: top; }
                    .alert {width:620px; margin-top: 5px; font-size: 85%;}
                    .banner {font-family:trebuchet ms,Arial, Helvetica; font-size: 125%; height: 30px; vertical-align: top; }
                    .info { background-color: #ffffff; font-size: 100%; width: 600px; line-height: 110%  }
                    .label {font-family:trebuchet ms, Arial, Helvetica; font-size: 85%; font-weight: bold; vertical-align: text-top; text-align: right;}
                    .tiny { font-size: 75%; }
                    .detail { font-size: 85%; background-color: #e0e0e0; margin-right: 20px; }
                    .headline { font-weight: bold; font-size: 105%; color:rgb(61,92,122)}

                </style>
            </head>
            <body>
                <table class="alert">
                    <tr>
                        <td class="headline" width="100%">
			Sahana Open Source Disaster Management System
                        </td>
                    </tr>
                </table>
                <table class="alert">         
                    <tr>
                        <td class="label">Message:</td>
                        <td>
                            <xs:value-of select="cap:identifier/text()"/>
                            <span class="tiny"> from </span>
                            <xs:value-of select="cap:sender/text()"/>
                            <span class="tiny"> sent at </span>
							
                            <xs:value-of select="substring(cap:sent/text(), 12, 5)"/>
                            <xs:variable name="offset">
                                <xs:value-of select="substring(cap:sent/text(), 20, 6)"/>
                            </xs:variable>
                            <xs:if test="$offset = '-08:00'">
                                <xs:text> PST</xs:text>
                            </xs:if>
                            <xs:if test="$offset = '-07:00'">
                                <xs:text> PDT</xs:text>
                            </xs:if>
                            <xs:if test="$offset = '-05:00'">
                                <xs:text> EST</xs:text>
                            </xs:if>
                            <xs:if test="$offset = '-04:00'">
                                <xs:text> EDT</xs:text>
                            </xs:if>
                            <xs:if test="$offset = '-00:00'">
                                <xs:text> GMT</xs:text>
                            </xs:if>
                            <xs:if test="$offset = '+00:00'">
                                <xs:text> GMT</xs:text>
                            </xs:if>
                            <span class="tiny"> on </span>
                            <xs:value-of select="substring(cap:sent/text(), 0, 11)"/>
							
                        </td>
                    </tr>
                    <tr>
                        <td><xs:text> </xs:text></td>
                        <td>
                            <xs:value-of select="cap:status/text()"/>
                            <xs:text>
                            </xs:text>
                            <xs:value-of select="cap:scope/text()"/>
                            <xs:text>
                            </xs:text>
                            <xs:value-of select="cap:msgType/text()"/>
                        </td>
                    </tr>
                    <xs:apply-templates/>
                </table>
            </body>
        </html>
    </xs:template>
	
    <xs:template match="cap:source">
        <tr>
            <td class="label">Source ID:</td>
            <td>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:restriction">
        <tr>
            <td class="label">Restriction:</td>
            <td>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:addresses">
        <tr>
            <td class="label">Addresses:</td>
            <td>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:code">
        <tr>
            <td class="label">Code:</td>
            <td>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:note">
        <tr>
            <td class="label">Note:</td>
            <td>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:references">
        <tr>
            <td class="label">Reference:</td>
            <td>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:incidents">
        <tr>
            <td class="label">Incidents:</td>
            <td>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <!-- Info block -->
	
    <xs:template match="cap:info">
        <tr>
            <td colspan="2">
                <table class="info">
                    <xs:apply-templates/>
                </table>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:language">
        <tr>
            <td class="label">Language:</td>
            <td>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:event">
        <tr>
            <td class="label">Event:</td>
            <td>
                <xs:value-of select="../cap:category/text()"/>
                <xs:text>: </xs:text>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:responseType">
        <tr>
            <td class="label">&gt;Response Type:</td>
            <td>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:urgency">
        <tr>
            <td class="label">Levels:</td>
            <td>
            <xs:value-of select="text()"/> -
            <xs:value-of select="../cap:severity/text()"/> -
            <xs:value-of select="../cap:certainty/text()"/> </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:audience">
        <tr>
            <td class="label">Intended Audience:</td>
            <td>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:eventCode">
        <tr>
            <td class="label">Code:</td>
            <td>
            <xs:value-of select="cap:valueName/text()"/> =
            <xs:value-of select="cap:value/text()"/> </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:effective">
        <tr>
            <td class="label">Effective:</td>
            <td>
                <xs:value-of select="substring(text(), 12, 5)"/>
                <xs:variable name="offset">
                    <xs:value-of select="substring(text(), 20, 6)"/>
                </xs:variable>
                <xs:if test="$offset = '-08:00'">
                    <xs:text> PST</xs:text>
                </xs:if>
                <xs:if test="$offset = '-07:00'">
                    <xs:text> PDT</xs:text>
                </xs:if>
                <xs:if test="$offset = '-05:00'">
                    <xs:text> EST</xs:text>
                </xs:if>
                <xs:if test="$offset = '-04:00'">
                    <xs:text> EDT</xs:text>
                </xs:if>
                <xs:if test="$offset = '-00:00'">
                    <xs:text> GMT</xs:text>
                </xs:if>
                <xs:if test="$offset = '+00:00'">
                    <xs:text> GMT</xs:text>
                </xs:if>
                <span class="tiny"> on </span>
                <xs:value-of select="substring(text(), 0, 11)"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:onset">
        <tr>
            <td class="label">Expected Onset:</td>
            <td>
                <xs:value-of select="substring(text(), 12, 5)"/>
                <xs:variable name="offset">
                    <xs:value-of select="substring(text(), 20, 6)"/>
                </xs:variable>
                <xs:if test="$offset = '-08:00'">
                    <xs:text> PST</xs:text>
                </xs:if>
                <xs:if test="$offset = '-07:00'">
                    <xs:text> PDT</xs:text>
                </xs:if>
                <xs:if test="$offset = '-05:00'">
                    <xs:text> EST</xs:text>
                </xs:if>
                <xs:if test="$offset = '-04:00'">
                    <xs:text> EDT</xs:text>
                </xs:if>
                <xs:if test="$offset = '-00:00'">
                    <xs:text> GMT</xs:text>
                </xs:if>
                <xs:if test="$offset = '+00:00'">
                    <xs:text> GMT</xs:text>
                </xs:if>
                <span class="tiny"> on </span>
                <xs:value-of select="substring(text(), 0, 11)"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:expires">
        <tr>
            <td class="label">Expires:</td>
            <td>
                <xs:value-of select="substring(text(), 12, 5)"/>
                <xs:variable name="offset">
                    <xs:value-of select="substring(text(), 20, 6)"/>
                </xs:variable>
                <xs:if test="$offset = '-08:00'">
                    <xs:text> PST</xs:text>
                </xs:if>
                <xs:if test="$offset = '-07:00'">
                    <xs:text> PDT</xs:text>
                </xs:if>
                <xs:if test="$offset = '-05:00'">
                    <xs:text> EST</xs:text>
                </xs:if>
                <xs:if test="$offset = '-04:00'">
                    <xs:text> EDT</xs:text>
                </xs:if>
                <xs:if test="$offset = '-00:00'">
                    <xs:text> GMT</xs:text>
                </xs:if>
                <xs:if test="$offset = '+00:00'">
                    <xs:text> GMT</xs:text>
                </xs:if>
                <span class="tiny"> on </span>
                <xs:value-of select="substring(text(), 0, 11)"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:senderName">
        <tr>
            <td class="label">From:</td>
            <td>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:headline">
        <tr>
            <td class="label">Headline:</td>
            <td class="headline">
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:description">
        <tr>
            <td class="label">Description:</td>
            <td>
                <!-- <xs:value-of select="text()"/> -->
                <pre>
                    <xs:value-of select="translate( normalize-space( translate( text(),'
','|') ),'|','
' )"/>
                </pre>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:instruction">
        <tr>
            <td class="label">Instructions:</td>
            <td>
                <pre>
                    <xs:value-of select="translate( normalize-space( translate( text(),'
','|') ),'|','
' )"/>
                </pre>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:web">
        <tr>
            <td class="label">Web:</td>
            <td> <a border="0">
                <xs:attribute name="href">
                    <xs:value-of select="text()"/>
                </xs:attribute>
                <xs:value-of select="text()"/> </a>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:contact">
        <tr>
            <td class="label">Contact:</td>
            <td>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:parameter">
        <tr>
            <td class="label">Parameter:</td>
            <td class="tiny">
            <xs:value-of select="cap:valueName/text()"/> =
            <xs:value-of select="cap:value/text()"/> </td>
        </tr>
    </xs:template>
	
    <!-- Resource block -->
	
    <xs:template match="cap:resource">
        <tr>
            <td class="label">Resource:</td>
            <td>
                <table class="detail">
                    <xs:apply-templates/>
                </table>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:resourceDesc">
        <tr>
            <td class="label">Description:</td>
            <td>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:mimeType">
        <tr>
            <td class="label">MIME Type:</td>
            <td>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:size">
        <tr>
            <td class="label">File Size (bytes):</td>
            <td>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:uri">
        <tr>
            <td class="label">URI:</td>
            <td> <a border="0">
                <xs:attribute name="href">
                    <xs:value-of select="text()"/>
                </xs:attribute>
                <xs:value-of select="text()"/> </a>
            </td>
        </tr>
    </xs:template>
	
    <!-- Area block -->
	
    <xs:template match="cap:area">
        <tr>
            <td class="label">Target Area:</td>
            <td>
                <table class="detail">
                    <xs:apply-templates/>
                </table>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:areaDesc">
        <tr>
            <td colspan="2">
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:polygon">
        <tr>
            <td class="label">Polygon:</td>
            <td>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:circle">
        <tr>
            <td class="label">Circle:</td>
            <td>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:geocode">
        <tr>
            <td class="label">Geocode:</td>
            <td>
            <xs:value-of select="cap:valueName/text()"/> =
            <xs:value-of select="cap:value/text()"/> </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:altitude">
        <tr>
            <td class="label">Altitude (ft.):</td>
            <td>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <xs:template match="cap:ceiling">
        <tr>
            <td class="label">Max. Altitude (ft.):</td>
            <td>
                <xs:value-of select="text()"/>
            </td>
        </tr>
    </xs:template>
	
    <!-- Ignore anything else -->
    <xs:template match="*"/>
	
</xs:stylesheet>
