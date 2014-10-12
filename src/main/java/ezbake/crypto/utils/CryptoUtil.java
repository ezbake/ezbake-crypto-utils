/*   Copyright (C) 2013-2014 Computer Sciences Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

package ezbake.crypto.utils;

import ezbake.crypto.RSAKeyCrypto;
import org.bouncycastle.util.encoders.Base64;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.spec.InvalidKeySpecException;

/**
 * User: jhastings
 * Date: 10/10/13
 * Time: 4:11 PM
 */
public class CryptoUtil {
    private static Logger logger = LoggerFactory.getLogger(CryptoUtil.class);

    public static byte[] der(String pem) {
        return decode(stripPEMString(pem));
    }

    public static String stripPEMString(String pem) {
        String ret = pem;
        pem = pem.replaceAll("\r\n", "\n");
        pem = pem.replaceAll("[ ]+", "");
        if (pem.startsWith("-----BEGIN") && (pem.endsWith("KEY-----") || pem.endsWith("KEY-----\n"))) {
            ret = "";
            String[] lines = pem.split("\n");
            for (int i = 1, len = lines.length-1; i < len; ++i) {
                ret += lines[i];
            }
        }
        ret = ret.replaceAll("\n", "");
        return ret;
    }

    public static String encode(byte[] data) {
        return new String(Base64.encode(data));
    }

    public static byte[] decode(String encoded) {
        return Base64.decode(encoded.getBytes());
    }


    public static byte[] load_p12(String ca, String cert, String privateKey) {
        byte[] pkcs12_bytes = new byte[0];
        try {
            CertificateFactory certificateFactory = CertificateFactory.getInstance("X.509");
            Certificate certificate = certificateFactory.generateCertificate(new ByteArrayInputStream(cert.getBytes()));
            Certificate cacert = certificateFactory.generateCertificate(new ByteArrayInputStream(ca.getBytes()));

            RSAKeyCrypto pkcrypto = new RSAKeyCrypto(privateKey, true);

            KeyStore ks = KeyStore.getInstance("PKCS12");
            ks.load(null, "password".toCharArray());
            ks.setKeyEntry("application", pkcrypto.getPrivateKey(), "password".toCharArray(), new Certificate[]{certificate, cacert});

            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            ks.store(bos, "password".toCharArray());

            pkcs12_bytes = bos.toByteArray();
        } catch (KeyStoreException e) {
            logger.error("Unable to load pkcs12", e);
        } catch (CertificateException e) {
            logger.error("Unable to load pkcs12", e);
        } catch (NoSuchAlgorithmException e) {
            logger.error("Unable to load pkcs12", e);
        } catch (IOException e) {
            logger.error("Unable to load pkcs12", e);
        } catch (InvalidKeySpecException e) {
            logger.error("Unable to load pkcs12", e);
        }

        return pkcs12_bytes;
    }
    public static byte[] load_jks(String x509cert) {
        byte[] jks_bytes = new byte[0];
        try {
            CertificateFactory certificateFactory = CertificateFactory.getInstance("X.509");
            Certificate certificate = certificateFactory.generateCertificate(new ByteArrayInputStream(x509cert.getBytes()));

            KeyStore ks = KeyStore.getInstance("JKS");
            ks.load(null, "password".toCharArray());
            ks.setCertificateEntry("ezbakeca", certificate);

            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            ks.store(bos, "password".toCharArray());

            jks_bytes = bos.toByteArray();
        } catch (KeyStoreException e) {
            logger.error("Unable to load jks", e);
        } catch (CertificateException e) {
            logger.error("Unable to load jks", e);
        } catch (NoSuchAlgorithmException e) {
            logger.error("Unable to load jks", e);
        } catch (IOException e) {
            logger.error("Unable to load jks", e);
        }

        return jks_bytes;
    }

}
