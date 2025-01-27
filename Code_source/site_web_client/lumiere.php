<?php
include 'db.php';

// Requête pour récupérer les 5 dernières mesures de température
$query = 'from(bucket: "Donnees_SolarEdge")
    |> range(start: -20y)
    |> filter(fn: (r) => r["_measurement"] == "luminosite")
    |> sort(columns: ["_time"], desc: true)
    |> limit(n: 3)';

try {
    $result = $client->createQueryApi()->query($query);
    $temperatures = [];
    foreach ($result as $table) {
        foreach ($table->records as $record) {
            $luminosite[] = [
                'heure' => $record->getTime(),
                'luminosite' => $record->getValue()
            ];
        }
    }
} catch (Exception $e) {
    die("Erreur : " . $e->getMessage());
}
?>

<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Mesures de Température</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <header>
        <nav>
            <ul>
                <li><a href="index.php">Accueil</a></li>
                <li><a href="temperature.php" class="active">Température</a></li>
                <li><a href="lumiere.php">Lumière</a></li>
		<li><a href="liste_puissance.html">Puissance</a></li>
                <li><a href="services.html">Nos services</a></li>
            </ul>
        </nav>
    </header>

    <main>
        <h1>Dernières Mesures de Luminosité</h1>
        <table>
            <thead>
                <tr>
                    <th>Heure</th>
                    <th>Luminosité  (lux)</th>
                </tr>
            </thead>
            <tbody>
                <?php foreach ($luminosite as $row): ?>
                <tr>
                    <td><?= date("Y-m-d H:i:s", strtotime($row['heure'])) ?></td>
                    <td><?= $row['luminosite'] ?> lux</td>
                </tr>
                <?php endforeach; ?>
            </tbody>
        </table>
    </main>
</body>
</html>
