<?php
require 'include/app.php';
redirectIfNotLogged();

if (!$_GET || !isset($_GET['id'])) {
    header('Location: account.php');
    exit();
}

// Find order
$order = queryDB('SELECT * FROM `orders` INNER JOIN `items` ON `items`.`id` = `orders`.`item_id` INNER JOIN `users` ON `users`.`id` = `orders`.`user_id` WHERE `orders`.`id` = ?', ['i', $_GET['id']]);
if (empty($order)) {
    header('Location: account.php');
    exit();
}
$order = $order[0];
?>
<!doctype html>
<html>
<head>
    <meta charset="utf-8">
    <title>Facture Goodies World</title>

    <style>
        .invoice-box {
            max-width: 800px;
            margin: auto;
            padding: 30px;
            border: 1px solid #eee;
            box-shadow: 0 0 10px rgba(0, 0, 0, .15);
            font-size: 16px;
            line-height: 24px;
            font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif;
            color: #555;
        }

        .invoice-box table {
            width: 100%;
            line-height: inherit;
            text-align: left;
        }

        .invoice-box table td {
            padding: 5px;
            vertical-align: top;
        }

        .invoice-box table tr td:nth-child(2) {
            text-align: right;
        }

        .invoice-box table tr.top table td {
            padding-bottom: 20px;
        }

        .invoice-box table tr.top table td.title {
            font-size: 45px;
            line-height: 45px;
            color: #333;
        }

        .invoice-box table tr.information table td {
            padding-bottom: 40px;
        }

        .invoice-box table tr.heading td {
            background: #eee;
            border-bottom: 1px solid #ddd;
            font-weight: bold;
        }

        .invoice-box table tr.details td {
            padding-bottom: 20px;
        }

        .invoice-box table tr.item td{
            border-bottom: 1px solid #eee;
        }

        .invoice-box table tr.item.last td {
            border-bottom: none;
        }

        .invoice-box table tr.total td:nth-child(2) {
            border-top: 2px solid #eee;
            font-weight: bold;
        }

        @media only screen and (max-width: 600px) {
            .invoice-box table tr.top table td {
                width: 100%;
                display: block;
                text-align: center;
            }

            .invoice-box table tr.information table td {
                width: 100%;
                display: block;
                text-align: center;
            }
        }

        /** RTL **/
        .rtl {
            direction: rtl;
            font-family: Tahoma, 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif;
        }

        .rtl table {
            text-align: right;
        }

        .rtl table tr td:nth-child(2) {
            text-align: left;
        }
    </style>
</head>

<body>
<div class="invoice-box">
    <table cellpadding="0" cellspacing="0">
        <tr class="top">
            <td colspan="2">
                <table>
                    <tr>
                        <td class="title">
                            Facture Goodies World
                        </td>

                        <td>
                            Facture #<?= $order['id'] ?><br>
                            Payé: <?= date('j M Y H:i', $order['created_at']) ?><br>
                        </td>
                    </tr>
                </table>
            </td>
        </tr>

        <tr class="heading">
            <td>
                Nom de l'article
            </td>

            <td>
                Prix
            </td>
        </tr>

        <tr class="item">
            <td>
                <?= $order['name']; ?>
            </td>

            <td>
                <?= $order['price']; ?>€
            </td>
        </tr>

        <tr class="total">
            <td></td>

            <td>
                Total: <?= $order['price']; ?>€
            </td>
        </tr>
    </table>
</div>
</body>
</html>