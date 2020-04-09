var pg = require('pg');

(async function main() {
	var pool = new pg.Pool({
		host: 'localhost',
		database: 'postgres',
		user: 'postgres',
		password: 'lemoniadka'
	});
	try {
		var result = await pool.query("INSERT INTO OSOBA (imie, nazwisko, plec)\
		 VALUES ('Bartek', 'Debesciak', 'm')");

		result.rows.forEach(r => {
			console.log(`${r.imie} ${r.nazwisko} ${r.plec}`);
		});
	} catch (err) {
		console.log(err);
	}
})();