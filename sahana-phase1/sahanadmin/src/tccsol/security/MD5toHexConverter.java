package tccsol.security;

/**
 * Copyright 2001-2004 The Apache Software Foundation.
 * <p/>
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * <p/>
 * http://www.apache.org/licenses/LICENSE-2.0
 * <p/>
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import java.security.*;

public class MD5toHexConverter {

    private static String hex(byte[] array) {
            StringBuffer sb = new StringBuffer();
            for (int i = 0; i < array.length; ++i) {
                sb.append(Integer.toHexString((array[i] & 0xFF) | 0x100).toUpperCase().substring(1,3));
            }
            return sb.toString();
        }

    public static String md5( String source )
    {
        try
        {
            MessageDigest md = MessageDigest.getInstance( "MD5" );
            byte[] bytes = md.digest( source.getBytes() );
            return hex( bytes );
        }
        catch( Exception e )
        {
            e.printStackTrace();
            return null;
        }
    }


    public static void main( String[] args )
    {
        if( args.length < 1 ){
            System.out.println( "Usage: word" );
            System.exit( 0 );
        }
        String word = args[ 0 ];
        System.out.println( "Word: " + word );
        System.out.println( " MD5: " + MD5toHexConverter.md5( word ) );
//        System.out.println( " SHA: " + MD5toHexConverter.sha( word ) );
    }
}
